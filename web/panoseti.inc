<?php

function page_head($title) {
    echo sprintf('
<!DOCTYPE html>
<html lang="en">
<head>
<title>%s</title>
<meta charset="utf-8">
<link type="text/css" rel="stylesheet" href="https://setiathome.berkeley.edu/panoseti/bootstrap.min.css" media="all">
<link rel=stylesheet type="text/css" href="https://setiathome.berkeley.edu/panoseti/sah_custom_dark.css">
</head>
<body >
',
    "PanoSETI: $title"
    );
    echo '<div class="container-fluid">';
    echo "<h2>$title</h2>";
}

function page_tail() {
    echo "</div></body></html>";
}

function get_int($key) {
    if (array_key_exists($key, $_GET)) {
        return (int)$_GET[$key];
    }
    return null;
}

function get_str($key) {
    if (array_key_exists($key, $_GET)) {
        return $_GET[$key];
    }
    return null;
}

// make sure a path doesn't go above current dir.
// Do this for any filename passed in a URL
//
function check_filename($name) {
    if (strstr($name, "..")) die("");
    if ($name[0] == "/") die("");
}

?>