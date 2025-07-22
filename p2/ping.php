<?php require 'utils.php'; require_login(); site_header('Ping Tool'); if($_SERVER['REQUEST_METHOD']==='POST'){ $host=$_POST['host']??''; $output=shell_exec("ping -c 1 $host 2>&1"); } ?>
<h2>Ping Tool <small style="font-size:.6em; color:#999;">You up?</small></h2>
<form method="POST">
  <input name="host" placeholder="127.0.0.1"> <button type="submit">Ping</button>
</form>
<pre><?= $output ?? '' ?></pre>
<?php site_footer(); ?>
