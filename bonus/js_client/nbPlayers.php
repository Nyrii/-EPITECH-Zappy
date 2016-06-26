<?php
session_start();

echo preg_match_all("/(pnw )/", $_SESSION['buff'], $matches);
