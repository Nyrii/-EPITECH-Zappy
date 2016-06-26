<?php
function aff($str) {
  echo "<p>" . $str . "</p>";
}

$ip = $_POST['ip'];
$port = $_POST['port'];
$theme = $_POST['theme'];
$team = "GRAPHIC\n";
session_start();
$_SESSION['ip'] = $ip;
$_SESSION['port'] = $port;
$_SESSION['theme'] = $theme;
$_SESSION['team'] = "GRAPHIC\n";
if (!$fd = stream_socket_client("tcp://$ip:$port", $errno, $errstr, 30)) {
  echo "KO";
  if ($errno == 101)
     exit(0);
  return (0);
}
$_SESSION['sock'] = $fd;
$st_buff = stream_socket_recvfrom($_SESSION['sock'], 512);
stream_socket_sendto($_SESSION['sock'], $_SESSION['team'], 0);
$buff = stream_socket_recvfrom($_SESSION['sock'], 10000);
stream_set_blocking($_SESSION['sock'], FALSE);
preg_match("/[0-9]{1,}/", $buff, $matches);
$size_x = $matches[0];
$buff = substr(strstr($buff, $size_x), 2);
preg_match("/[0-9]{1,}/", $buff, $matches);
$size_y = $matches[0];
$_SESSION['size_x'] = $size_x;
$_SESSION['size_y'] = $size_y;
$_SESSION['buff'] = substr(strstr($buff, "sgt"), 0);
preg_match("/sgt [1-9]{1}[0-9]{0,6}/", $_SESSION['buff'], $matches);
preg_match("/[1-9]{1}[0-9]{0,6}/", $matches[0], $tmp);
$_SESSION['sgt'] = substr($matches[0], - $matches[0] - ($matches[0] - 4));
$_SESSION['buff'] = substr(strstr($_SESSION['buff'], "bct"), 0);
echo json_encode(array("size_x" => $size_x, "size_y" => $size_y, "theme" => $theme));
unset($_SESSION['size_x']);
unset($_SESSION['size_y']);
