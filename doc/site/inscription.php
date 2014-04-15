<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta name="author" content="Lecoconnier David" />
		<meta name="category" content="Logiciel" />
		<meta name="language" content="fr" />
		<meta name="description" content="Inscrivez-vous sur le site de Fu(X) pour rester inform&eacute; des derni&egrave;res nouveaut&eacute;s ! Participez &agrave; la conception du logiciel." />
		<meta name="keywords" content="Fu(X), Fu(X) 2.0, 2.0, Fux, musique, rapide, simple, lecteur, audio, mp3, m3u, tag, liste, gestion, interface, claire, efficace, explorateur, glisser, d&eacute;poser" />
		<meta name="robots" content="all" />
		<meta http-equiv="content-language" content="french" />
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Inscription</title>
		<link rel="stylesheet" type="text/css" href="./Styles/style.css" media="screen" />
		<link rel="icon" type="image/png" href="images/play.png" />
	</head>
	<body>
		<?php
			include("menu.php");
			require("bdd.php");
		?>	
		
		<div id="corps">
			<?php $page_actuelle='inscription.php'; include("droite.php"); ?>
			<div id="milieu">
				<div id="description">
				<?php
					$num_news = 0;
					$afficheAjoutCom = false;
					if (isset($_GET['num_news']))
						$num_news = intval($_GET['num_news']);
				?>
					<h3>Inscription</h3>
					<form action="inscription_post.php" method="post">
						<p>
							<table id="centre">
								<tr>
									<td><label for="idpseudo">Pseudo</label></td>
									<td><input type="text" name="pseudo" id="idpseudo" size="70" maxlength="255" /></td>
								</tr>
								<tr>
									<td><label for="idmdp">Mot de passe</label></td>
									<td><input type="password" name="mdp" id="idmdp" size="70" maxlength="255" /></td>
								</tr>
								<tr>
									<td><label for="idmdp2">Mot de passe (bis)</label></td>
									<td><input type="password" name="mdp2" id="idmdp2" size="70" maxlength="255" /></td>
								</tr>
								<tr>
									<td><label for="idmail">Votre adresse mail</label></td>
									<td><input type="text" name="mail" id="idmail" size="70" maxlength="255" /></td>
								</tr>
								<tr>
									<td>Souhaitez-vous recevoir des newsletter ?</td>
									<td>
										<label for="idnews">oui</label><input type="radio" name="news" id="idnews" value="oui" checked="checked" />
										<label for="idnews2">non</label><input type="radio" name="news" id="idnews2" value="non" />
									</td>
								</tr>
								<tr>
									<td><label for="idsite">Votre site web</label></td>
									<td><input type="text" name="site" id="idsite" size="70" maxlength="255" /></td>
								</tr>
								<tr>
									<td><label for="idcitation">Votre citation</label></td>
									<td><textarea name="citation" id="idcitation" cols="100" rows="6"></textarea></td>
								</tr>
								<tr>
									<td><input type="hidden" name="num_news" value="<?php echo $num_news; ?>" /></td>
									<td><input type="submit" value="Valider" /></td>
								</tr>
							</table>
						</p>
					</form>
				</div>
				<div id="actu">
					<h3>Informations</h3>
					<p>Votre inscription vous permet de participer &agrave; la vie du site et de recevoir des mails sur les derni&egrave;res versions de Fu(X). Votre adresse mail ne sera en aucun transmis &agrave; un service/entreprise tiers.</p>
				</div>
			</div>
		</div>
		
		<?php include("piedPage.php"); ?>
		
	</body>
</html>