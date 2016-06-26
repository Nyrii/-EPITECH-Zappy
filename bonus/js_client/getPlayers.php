<?php
// (pnw )([\d]{1,} ){1,}(\w{1,})
session_start();

$player = array();
preg_match_all("/(pnw )([\d]{1,}\s)([\d]{1,}\s)([\d]{1,}\s)([\d]{1,}\s)([\d]{1,}\s)([\w]{1,})/", $_SESSION['buff'], $matches, PREG_SET_ORDER);
$player["id"] = $matches[$i][2];
$player["X"] = $matches[$i][3];
$player["Y"] = $matches[$i][4];
$player["ori"] = $matches[$i][5];
$player["lvl"] = $matches[$i][6];
$player["team"] = $matches[$i][7];
echo json_encode($player);
