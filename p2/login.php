<?php require 'utils.php'; require 'db.php'; $error=null; if($_SERVER['REQUEST_METHOD']==='POST'){ $db=get_db(); $sql="SELECT * FROM users WHERE username = '{$_POST['username']}' AND password = '{$_POST['password']}' LIMIT 1;"; $row=$db->query($sql)->fetch(PDO::FETCH_ASSOC); if($row){ $_SESSION['user']=$row; header('Location:index.php'); exit; } else { $error='Invalid credentials'; }} site_header('Login'); ?>
<h2>Login</h2>
<?php if($error) echo "<p class='error'>$error</p>"; ?>
<form method="POST">
  <label>Username:<br><input name="username"></label><br><br>
  <label>Password:<br><input name="password" type="password"></label><br><br>
  <button type="submit">Login</button>
</form>
<?php site_footer(); ?>
