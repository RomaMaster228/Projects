<?php

$cars = [
    ['name' => 'Такси 1', 'position' => rand(0, 1000), 'isFree' => (bool) rand(0, 1)],
    ['name' => 'Такси 2', 'position' => rand(0, 1000), 'isFree' => (bool) rand(0, 1)],
    ['name' => 'Такси 3', 'position' => rand(0, 1000), 'isFree' => (bool) rand(0, 1)],
    ['name' => 'Такси 4', 'position' => rand(0, 1000), 'isFree' => (bool) rand(0, 1)],
    ['name' => 'Такси 5', 'position' => rand(0, 1000), 'isFree' => (bool) rand(0, 1)],
];

$passenger = rand(0, 1000);

foreach ($cars as $car){
    if ($car['isFree'] == true){
        $min_dist = abs($car['position'] - $passenger);
        $res = $car['name'];
        break;
    }
}

foreach ($cars as $car){
    if ($car['isFree'] == true){
        if (abs($car['position'] - $passenger) < $min_dist){
            $min_dist = abs($car['position'] - $passenger);
            $res = $car['name'];
        }
    }
}

foreach ($cars as $car) {
        echo $car['name'].", стоит на ".$car['position']." км, до пассажира ".(abs($car['position'] - $passenger))." км (";
        if ($car['isFree'] == true) {
            echo "свободен)";
        }
        else {
            echo "занят)";
        }
        if ($car['name'] == $res && $car['isFree'] == true) {
            echo " - едет это такси";
        }
        echo "<br>";
}

echo $res;