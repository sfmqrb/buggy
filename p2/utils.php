<?php
session_start();
function current_user() {
    return $_SESSION['user'] ?? null;
}
function require_login() {
    if (!current_user()) {
        header("Location: login.php");
        exit;
    }
}
?>
