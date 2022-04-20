<?php
function echo_nb_lign($file)
{
  $out = [];
  exec("wc -l data/arbre" . $file, $out);
  $res = explode(" ", $out[0])[0] + 1;
  $disp = "Nombre-de-lignes réel : "  . $res . "\n";
  return [$res, $disp];
}

function nb_func_c($file, $func, $params = 0)
{
  $out = [];
  exec("./a234 data/arbre" . $file . " " . $func . " " . $params, $out);
  $disp = implode("\n", $out);
  $disp .= "\n";
  $res = explode(" ", $out[count($out) - 1]);
  $res = $res[count($res) - 1];
  return [$res, $disp];
}

function echo_a234($file)
{
  $out = [];
  exec("./a234 data/arbre" . $file . " display", $out);
  $disp =  "Arbre " . $file . " : \n ";
  $disp .= implode("\n", $out);
  $disp .= "\n";
  echo $disp;
}

function test_nombre_cles($i)
{
  [$lign_c, $disp_c] = nb_func_c($i, "nb_cles");
  [$lign_r, $disp_r] = echo_nb_lign($i);
  if ($lign_c == $lign_r) {
    echo "Arbre " . $i . " : OK\n";
  } else {
    echo "Arbre " . $i . " : KO\n";
    echo $disp_c;
    echo $disp_r;
  }
}

function max_a234($file)
{
  $tab = file("data/arbre" . $file);
  $max = -1;
  foreach ($tab as $num) {
    if ($num > $max) {
      $max = $num;
    }
  }
  return $max;
}

function test_cle_max($i)
{
  [$cle_max_c, $disp_c] = nb_func_c($i, "cle_max");
  $cle_max = max_a234($i);
  $disp_r = "Cle max réel : " . $cle_max . "\n";
  if ($cle_max_c == $cle_max) {
    echo "Arbre " . $i . " : OK\n";
  } else {
    echo "Arbre " . $i . " : KO\n";
    echo $disp_c;
    echo $disp_r;
  }
}

function min_a234($file)
{
  $tab = file("data/arbre" . $file);
  $min = 1000000;
  foreach ($tab as $num) {
    if ($num < $min) {
      $min = $num;
    }
  }
  return $min;
}

function test_cle_min($i)
{
  [$cle_max_c, $disp_c] = nb_func_c($i, "cle_min");
  $cle_min = min_a234($i);
  $disp_r = "Cle min réel: " . $cle_min . "\n";
  if ($cle_max_c == $cle_min) {
    echo "Arbre " . $i . " : OK\n";
  } else {
    echo "Arbre " . $i . " : KO\n";
    echo $disp_c;
    echo $disp_r;
  }
}

function test_recherche_cle($i)
{
  $is_cle_r = file("data/arbre" . $i);
  $is_not_cle_r = [];

  while (count($is_not_cle_r) != 10) {
    $rand = rand(1, 1000);
    if (!in_array($rand, $is_cle_r)) {
      $is_not_cle_r[] = $rand;
    }
  }

  // print_r(["is" => $is_cle_r, "is_not" => $is_not_cle_r]);

  foreach ($is_cle_r as $cle_r) {
    [$is_cle_c, $disp_c] = nb_func_c($i, "recherche_cle", $cle_r);
    if (!$is_cle_c) {
      echo "Arbre " . $i . " : KO\n";
      echo $disp_c;
      echo "Recherche-de-la-cle-" . $cle_r . " : 0\n";
      echo_a234($i);
      return;
    }
  }

  foreach ($is_not_cle_r as $not_cle_r) {
    [$is_cle_c, $disp_c] = nb_func_c($i, "recherche_cle", $not_cle_r);
    if ($is_cle_c) {
      echo "Arbre " . $i . " : KO\n";
      echo $disp_c;
      echo "Recherche-de-la-cle-" . $not_cle_r . " : 0\n";
      echo_a234($i);
      return;
    }
  }

  echo "Arbre " . $i . " : OK\n";
}

function test_analyse_struct($i)
{
  $lign_r = echo_nb_lign($i)[1];
  $disp_c = nb_func_c($i, "analyse_struct")[1];
  echo_a234($i);
  echo $disp_c;
  $disp_c = explode("\n", $disp_c);
  $nb = 0;
  for ($i = 0; $i <= 3; $i++) {
    $nb += explode(":", $disp_c[$i])[1];
  }
  if ($nb != $lign_r) {
    echo "Arbre " . $i . " : KO\n";
    echo $lign_r;
    echo "Nombre d'éléments : " . $nb . "\n";
  } else {
    echo "Arbre " . $i . " : OK\n";
  }
}

function test_noeud_max($i){
  echo_a234($i);
  echo nb_func_c($i, "noeud_max")[1];
}

exec("make");
if (isset($argv[1])) {
  switch ($argv[1]) {
    case "nb_cles":
      echo "Test Nombre clés\n";
      for ($i = 1; $i <= 16; $i++) {
        test_nombre_cles($i);
        echo "\n";
      }
      echo "Done\n\n";
      break;
    case "cle_max":
      echo "Test clé max\n";
      for ($i = 1; $i <= 16; $i++) {
        test_cle_max($i);
        echo "\n";
      }
      echo "Done\n";
      break;
    case "cle_min":
      echo "Test clé min\n";
      for ($i = 1; $i <= 16; $i++) {
        test_cle_min($i);
        echo "\n";
      }
      echo "Done\n";
      break;
    case "recherche_cle":
      echo "Test Recherche clé\n";
      for ($i = 1; $i <= 16; $i++) {
        test_recherche_cle($i);
        echo "\n";
      }
      echo "Done\n";
      break;
    case "analyse_struct":
      echo "Test Analyse struct\n";
      for ($i = 1; $i <= 16; $i++) {
        test_analyse_struct($i);
        echo "\n";
      }
      echo "Done\n";
      break;
    case "noeud_max":
      echo "Test Noeud max\n";
      for ($i = 1; $i <= 16; $i++) {
        test_noeud_max($i);
        echo "\n";
      }
      echo "Done\n";
      break;
    default:
      echo "Paramètre inconnue\n";
      break;
  }
} else {
  echo "Il manque le parametre test\n";
}
exec("make clean");
