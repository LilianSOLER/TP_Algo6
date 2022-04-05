<?php

function test_all()
{
  exec("make");
  for ($i = 1; $i <= 16; $i++) {
    $out = [];
    exec("./a234 data/arbre" . $i, $out);
    echo "Arbre " . $i . " : \n ";
    echo implode("\n", $out);
  }

  $out = [];
  exec("./a234 data/arbrecours", $out);
  echo "Arbre cours : \n ";
  echo implode("\n", $out);

  exec("make clean");
}

test_all();
