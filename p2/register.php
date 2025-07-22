<?php require 'utils.php'; require 'db.php'; if($_SERVER['REQUEST_METHOD']==='POST'){ $db=get_db(); $sql="INSERT INTO users(username,password) VALUES ('{$_POST['username']}', '{$_POST['password']}')"; try { $db->exec($sql); echo "<p>Registered! <a href='login.php'>Login</a></p>"; exit; } catch(Exception $e){ echo "<p class='error'>Error: ".htmlspecialchars($e->getMessage())."</p>"; }} site_header('Register'); ?>
<h2>Create Account</h2>
<form method="POST">
  <label>Username:<br><input name="username"></label><br><br>
  <label>Password:<br><input name="password" type="password"></label><br><br>
  <button type="submit">Register</button>
</form>
<?php site_footer(); ?>
