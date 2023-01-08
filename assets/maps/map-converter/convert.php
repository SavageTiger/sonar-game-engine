<?php

$mapLayout = file_get_contents('test.floorplan');
$mapLayout = str_replace("\r", "\n", $mapLayout);
$mapLayout = preg_replace("/\n+/", "\n", $mapLayout);

$ceilingLayout = file_get_contents('test.ceilingplan');
$ceilingLayout = str_replace("\r", "\n", $ceilingLayout);
$ceilingLayout = preg_replace("/\n+/", "\n", $ceilingLayout);

$textureSettings = new DOMDocument('1.0', 'UTF-8');
$textureSettings->load('textures.xml');

$availableTextures = [];
$usedTextures = [];

foreach ($textureSettings->getElementsByTagName('texture') as $node) {
    $availableTextures[(int) $node->getAttribute('id')] = $node->nodeValue;
}

$magic = 'SGMV1';
$mapLayoutOutput = '';
$textureOutput = '';

for ($i = 0; $i < strlen($mapLayout); $i++) {
    $blockSizeInBytes = 10;

    if ($mapLayout[$i] === "\n") {
        $mapLayoutOutput .= str_repeat("\0", $blockSizeInBytes);
    } else {
        $usedTextures[$mapLayout[$i]] = $availableTextures[$mapLayout[$i]];
        $usedTextures[$ceilingLayout[$i]] = $availableTextures[$ceilingLayout[$i]];

         $tileData = [
            'tileType' => getTileType($mapLayout[$i], $textureSettings),
            'wallTextureId' => $mapLayout[$i],
            'floorTextureId' => 0,
            'ceilingTextureId' => $ceilingLayout[$i],
            'thickness' => getTileType($mapLayout[$i], $textureSettings) == 3 ? 40 : 100,
        ];

        $mapLayoutOutput .= pack(
            "nnnnn",
            $tileData['tileType'],
            $tileData['wallTextureId'],
            $tileData['floorTextureId'],
            $tileData['ceilingTextureId'],
            $tileData['getThickness']
        );
    }
}

ksort($usedTextures);

foreach ($usedTextures as $texture) {
    $textureOutput .= pack("n", strlen($texture)) . $texture;
}

file_put_contents('../test.sgm',
    $magic .
    pack("N", strlen($mapLayoutOutput)) .
    $mapLayoutOutput .
    pack("N", strlen($textureOutput)) .
    $textureOutput
);

function getTileType(int $wallTextureId, DOMDocument $textureSettings) : int
{
    $wallsNode = $textureSettings->getElementsByTagName('walls')->item(0);
    $doorsNode = $textureSettings->getElementsByTagName('doors')->item(0);

    foreach ($wallsNode->childNodes as $node) {
        if ($node->nodeName === 'texture-id') {
            if ((int) $node->nodeValue === $wallTextureId) {
                return 2;
            }
        }
    }

    foreach ($doorsNode->childNodes as $node) {
        if ($node->nodeName === 'texture-id') {
            if ((int) $node->nodeValue === $wallTextureId) {
                return 3;
            }
        }
    }

    return 1;
}
