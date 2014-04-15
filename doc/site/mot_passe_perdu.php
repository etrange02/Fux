<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta name="author" content="Lecoconnier David" />
		<meta name="category" content="Logiciel, Explorateur" />
		<meta name="language" content="fr" />
		<meta name="robots" content="none" />
		<meta http-equiv="content-language" content="french" />
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Accueil</title>
		<link rel="stylesheet" type="text/css" href="./Styles/style.css" media="screen" />
		<link rel="icon" type="image/png" href="images/play.png" />
	</head>
	<body>
		<?php
			include("menu.php");
			require("bdd.php");
		?>
		
		<div id="corps">
			<?php $page_actuelle='mot_passe_perdu.php'; include("droite.php"); ?>
			<?php
				$pseudo = '';
				if (isset($_POST['pseudoPerd']) && !empty($_POST['pseudoPerd']))
				{
					$pseudo = htmlentities($_POST['pseudoPerd'], ENT_QUOTES, 'UTF-8');
					
					$requete = 'SELECT mail, mdp FROM utilisateur WHERE pseudo=\''.$pseudo.'\'';
					$resultat = $bdd->query($requete);
					$ligne = $resultat->fetch();
					
					$message = '<html><head><meta http-equiv="Content-Type" content="text/html; charset=utf-8"></head><body><p>';
					$message .= 'Vous venez de demander votre mot de passe.<br />Votre mot de passe est <u>'.$ligne['mdp'].'</u>.<br /><br />A bient&ocirc;t sur <a href="http://www.fuxplay.com">www.fuxplay.com</a>, etrange02';
					$message .= '</p></body></html>';
					
					$headers = 'MIME-Version: 1.0'."\r\n";
					$headers .= 'Content-type: text/html; charset=utf-8'."\r\n";
					
					$message = wordwrap($message, 70);						
					
					if (mail($ligne['mail'], 'Fu(X) : votre mot de passe [message automatique]', $message, $headers.'From: fux@fuxplay.com'))
						echo '<p>Un mail avec votre mot de passe a &eacute;t&eacute; envoy&eacute; &agrave; l\'adresse que vous avez utilis&eacute; pour vous enregistrer.</p>';
					else
						echo '<p>Un probl&egrave;me a emp&ecirc;ch&eacute; l\'envoi du courriel, veuillez contacter un admin &agrave; cette adresse : fux@fuxplay.com</p>';
					$resultat->closeCursor();
				}
			?>
			<div id="milieu">
				<div id="description">
					<h3>Mot de passe perdu</h3>
					<form method="post" action="mot_passe_perdu.php">
						<p>
							<table id="centre">
								<tr>
									<td><label for="idpseudo">Pseudo</label></td>
									<td><input type="text" name="pseudoPerd" id="idpseudo" size="70" maxlength="255" value="<?php echo $pseudo; ?>" /></td>
								</tr>
								<tr>
									<td></td>
									<td><input type="submit" value="Envoyer" /></td>
								</tr>
							</table>
						</p>
					</form>
				</div>
			</div>
		</div>
		
		<?php include("piedPage.php"); ?>
		
	</body>
</html>