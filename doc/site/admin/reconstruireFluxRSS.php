<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Administration Version</title>
		<?php
			include("../bdd.php"); 
			include("flux_rss.php");
		?>
	</head>
	<body>
		<h1>Administration du site</h1>
		<p><a href="../index.php">Accueil du site</a></p>
		<p><a href="index.php">Accueil administration</a></p>
		<?php
			if (isset($_SESSION['admin']) && $_SESSION['admin'] == true)
			{
				echo '<p>Bienvenue '.$_SESSION['pseudo'].'</p>';
				?>
					<form action="index.php" method="post">
						<p>
							<input type="submit" value="D&eacute;connexion" />
							<input type="hidden" name="deco" value="on" />
						</p>
					</form>
					<form action="<?php $PHP_SELF;?>" method="post">
						<legend>Reconstruire le flux RSS ??</legend>
						<input type="submit" value="Reconstruire" name="reconstruireFlux" />
					</form>
				<?php
				if (isset($_POST['reconstruireFlux']))
				{
					rebuild_rss($bdd);
					echo '<p>Fichier reconstruit.</p>';
				}
			}
			else
				header('Location: index.php');
		?>
		
	</body>
</html>