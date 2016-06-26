<?php
session_start();

$team = array();
preg_match_all("/(tna )[\w]{1,}/", $_SESSION['buff'], $matches);
$i = 0;
while ($matches[0][$i]) {
  $team[$i] = substr($matches[0][$i], - $matches[0][$i] - ($matches[0][$i] - 4));
  $i++;
}
$_SESSION['team'] = $team;
echo json_encode($team);
