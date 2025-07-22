<?php
session_start();
function current_user() { return $_SESSION['user'] ?? null; }
function require_login() { if (!current_user()) { header('Location: login.php'); exit; } }
function site_header($title='VulnApp') { ?>
<!DOCTYPE html><html><head><meta charset="utf-8"><title><?= $title ?></title>
<style>
body {font-family: system-ui, Arial; background:#f5f5f7; margin:0;}
header {background:#222; color:#fff; padding:10px 20px; display:flex; align-items:center; justify-content:space-between;}
header a {color:#eee; margin-right:15px; text-decoration:none; font-weight:bold;}
header a:hover {text-decoration:underline;}
.container {max-width:900px; margin:20px auto; background:#fff; padding:20px 30px; border-radius:8px; box-shadow:0 2px 4px rgba(0,0,0,.1);} 
nav {margin-bottom:15px;} 
nav a.btn {display:inline-block; background:#0366d6; color:#fff; padding:6px 12px; border-radius:4px; margin-right:6px; text-decoration:none;} 
nav a.btn.secondary {background:#555;} 
textarea, input[type=text], input[type=password] {width:100%; padding:8px; border:1px solid #ccc; border-radius:4px;}
input[type=password]{width:250px; padding:8px; border:1px solid #ccc; border-radius:4px;}
button, input[type=submit] {background:#0366d6; color:#fff; border:none; padding:8px 14px; border-radius:4px; cursor:pointer;}
button:hover, input[type=submit]:hover {background:#024f9e;}
.message {padding:8px 10px; border-bottom:1px solid #eee;} 
.user-tag {background:#ffd54f; padding:2px 6px; border-radius:4px; font-size:.8em; margin-right:4px;} 
pre {background:#222; color:#0f0; padding:10px; border-radius:6px; overflow:auto;} 
.error {color:#b00020; font-weight:bold;} 
footer {text-align:center; padding:20px; font-size:.8em; color:#666;} 
</style></head><body>
<header>
  <div><strong>VulnApp</strong></div>
  <div>
    <?php if (current_user()): ?>
      <span style="margin-right:10px;">Hello, <strong><?= current_user()['username'] ?></strong></span>
      <a href="index.php">Home</a>
      <a href="message.php">Post</a>
      <a href="logout.php">Logout</a>
      <a href="search.php">Search</a>
      <a href="ping.php">Ping</a>
    <?php else: ?>
      <a href="index.php">Home</a>
      <a href="login.php">Login</a>
      <a href="register.php">Register</a>
    <?php endif; ?>
  </div>
</header>
<div class="container">
<?php }
function site_footer() { ?>
</div><footer>VulnApp training playground – insecure by design.</footer></body></html>
<?php } ?>
