<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Administration Newsletter</title>
		<?php require("../bdd.php"); ?>
	</head>
	<body>
		<h1>Administration du site</h1>
		<p><a href="../index.php">Accueil du site</a></p>
		<p><a href="index.php">Accueil administration</a></p>
		<?php
			if (isset($_SESSION['admin']) && $_SESSION['admin'] == true)
			{
				echo '<p>Bienvenue '.$_SESSION['pseudo'].'</p>';
				
				$resultat = $bdd->query('SELECT mail FROM utilisateur WHERE id='.$_SESSION['idpseudo']);
				$ligne = $resultat->fetch();
				$mail = $ligne['mail'];
				$resultat->closeCursor();
				?>
					<form action="index.php" method="post">
						<p>
							<input type="submit" value="D&eacute;connexion" />
							<input type="hidden" name="deco" value="on" />
						</p>
					</form>
					<form action="<?php $PHP_SELF;?>" method="post">
						<fieldset>
							<legend>Envoi de newsletter (Attention au code html entr&eacute;, il est pris en compte)</legend>
							<table>
							<tr>
								<td><label for="idtitre">Titre</label></td>
								<td><input type="text" id="idtitre" name="titre" maxlength="255" <?php if (isset($_POST['envMail'])) echo 'value="'.$_POST['titre'].'"'; ?> /></td>
							</tr>
							<tr>
								<td><label for="idexpediteur">Exp&eacute;diteur (ou fux@fuxplay.com)</label></td>
								<td><input type="text" id="idexpediteur" name="expediteur" size="100" maxlength="255" value="fux@fuxplay.com" /></td><?php echo $mail; ?>
							</tr>
							<tr>
								<td><label for="idtexte">News</label></td>
								<td><textarea id="idtexte" name="texte" cols="100" rows="7"><?php if (isset($_POST['envMail'])) echo $_POST['texte']; ?></textarea></td>
							</tr>
							<tr>
								<td></td>
								<td><input type="submit" value="Envoyer" name="envMail" /></td>
							</tr>
						</fieldset>
					</form>
				<?php
				if (isset($_POST['envMail']) && isset($_POST['titre']) && isset($_POST['texte']))
				{
					$titre = $_POST['titre'];
					$auteur = $_POST['expediteur'];
					$i = 0;
					
					// Dans le cas o� nos lignes comportent plus de 70 caract�res, nous les coupons en utilisant wordwrap()
					
					$message = str_replace('\"', '"', $_POST['texte']);
					$message = nl2br($message);
					$message = '<html><head><meta http-equiv="Content-Type" content="text/html; charset=utf-8"></head><body><p>'.$message.'</p></body></html>';
					
					$headers = 'MIME-Version: 1.0'."\r\n";
					$headers .= 'Content-type: text/html; charset=utf-8'."\r\n";
					
					$message = wordwrap($message, 70);					
					
					$resultat = $bdd->query('SELECT mail, pseudo FROM utilisateur WHERE newsletter=1');
					while ($ligne = $resultat->fetch())
					{
						mail($ligne['mail'], $titre, $message, $headers.'From : '.$auteur);
						$i++;
					}
					echo '<p>Mails envoy&eacute;s : '.$i.'/'.$resultat->rowCount().'</p>';
					echo '<p id="cadre">'.$message.'</p>';
					$resultat->closeCursor();
				}
			}
			else
				header('Location: index.php');
		?>
		
	</body>
</html>