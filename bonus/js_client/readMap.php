<?php
session_start();

preg_match("/(bct )(\d{1,}\s){9}/", $_SESSION['buff'], $matches);
$_SESSION['buff'] = substr(strstr($_SESSION['buff'], "bct"), 21);
preg_match("/(\d{1,}\s){9}/", $matches[0], $tmp);
$string = substr($matches[0], 4);
$array = array();
$array["X"] = strtok($string, " ");
$array["Z"] = strtok(" ");
$array["food"] = strtok(" ");
$array["linemate"] = strtok(" ");
$array["deraumere"] = strtok(" ");
$array["sibur"] = strtok(" ");
$array["mendiane"] = strtok(" ");
$array["phiras"] = strtok(" ");
$array["thystame"] = strtok(" ");
echo json_encode($array);
