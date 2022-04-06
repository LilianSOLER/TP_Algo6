<?php
function echo_nb_lign($file)
{
  $out = [];
  exec("wc -l data/arbre" . $file, $out);
  $res = explode(" ", $out[0])[0] + 1;
  $disp = "Nombre de lignes : "  . $res . "\n";
  return [$res, $disp];
}

function echo_a234($file)
{
  $out = [];
  exec("./a234 data/arbre" . $file, $out);
  $disp =  "Arbre " . $file . " : \n ";
  $disp .= implode("\n", $out);
  $disp .= "\n";
  $res = explode(" ", $out[count($out) - 1]);
  $res = $res[count($res) - 1];
  return [$res, $disp];
}

function test_nombre_cles($i)
{
  [$lign_c, $disp_c] = echo_a234($i);
  [$lign_r, $disp_r] = echo_nb_lign($i);
  if ($lign_c == $lign_r) {
    echo "Arbre " . $i . " : OK\n";
  } else {
    echo "Arbre " . $i . " : KO\n";
    echo $disp_c;
    echo $disp_r;
  }
}

function test_all()
{
  exec("make");
  for ($i = 1; $i <= 16; $i++) {
    test_nombre_cles($i);
    echo "\n";
  }

  test_nombre_cles("cours");

  exec("make clean");
}

test_all();
