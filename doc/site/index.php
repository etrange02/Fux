<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>Fu(X) 2.0 - Accueil</title>
		<meta name="description" content="Ecoutez vos musiques simplement et efficacement, et modifiez le contenu de votre lecteur MP3 en 2 clics !" />
		<meta name="abstract" content="Lecteur audio g&eacute;rant les mp3, m3u et les tags" />
		<meta name="author" content="Lecoconnier David" />
		<meta name="category" content="Logiciel, Explorateur" />
		<meta name="language" content="fr" />
		<meta name="keywords" content="Fux, Fu(X), Fux 2.0, fix, fyx, fixplay, fuc, musique, mp3, rapide, simple, lecteur, audio, m3u, tag, liste, gestion, interface, claire, efficace, explorateur, exploration, glisser, d&eacute;poser" />
		<meta name="robots" content="all" />
		<meta http-equiv="content-language" content="french" />
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<link rel="stylesheet" type="text/css" href="./Styles/style.css" media="screen" />
		<link rel="icon" type="image/png" href="images/play.png" />
		<link rel="alternate" type="application/rss+xml" title="Fu(X) 2.0 - T&eacute;l&eacute;chargement" href="download_fux_rss.xml" />
	</head>
	<body>
		<?php
			include("menu.php");
			require("bdd.php");
		?>
		
		<div id="corps">
			<?php $page_actuelle='index.php'; include("droite.php"); ?>
			<div id="milieu">
				<div id="description">
					<h3>Description</h3>
					<p>Fu(X) est un lecteur audio. Encore un certains diront ! Je ne peux que confirmer cette remarque, mais le but est de ne pas faire comme les autres.<br /><br />Fu(X) lit principalement les mp3 et g&egrave;re les TAGs. L'interface se veut simple et intuitive. Cela n'emp&ecirc;che pas d'avoir des outils plus avanc&eacute;s !<br />
					Il est capable de cr&eacute;er et g&eacute;rer des m3u, et peut remplacer l'explorateur de votre syst&egrave;me d'exploitation dans l'onglet "Exploitation". Fu(X) est portable : il peut fonctionner sur une clef USB (version a5). Pour plus d'information, vous pouvez aller dans la partie <a href="aide.php">aide</a>.<br /><br />
					Il lui manque encore certains outils comme l'audioth&egrave;que et la gestion des produits de la marque &agrave; la pomme.</p>										<p><a href="images/fux_vueeclate.jpg" title="On s'&eacute;clate avec Fu(X) ;)"><img class="image_fux_grand" src="images/fux_vueeclate.jpg" alt="&Eacute;clatage de Fu(X)" /></a></p>
				</div>
				<div id="actu">
					<h3>Actualit&eacute;</h3>
					<?php
						$requete = 'SELECT * FROM news ORDER BY id DESC LIMIT 0, 5';
						$resultat = $bdd->query($requete);
						
						if ($resultat->rowCount() == 0)
							echo "<p>Aucune news n'est actuellement disponible.</p>";
						else
						{
							$res2 = 0;
							while($donnee = $resultat->fetch())
							{
								$res2 = $bdd->query('SELECT * FROM utilisateur where id="'.$donnee['auteur'].'"');
								$ligne = $res2->fetch();
								echo '<div class="info"><h4>'.$donnee['titre'].' <span class="auteur">par '.$ligne['pseudo'].' le '.$donnee['date'].'</span></h4>';
																
								$res2 = $bdd->query('SELECT COUNT(*) FROM commentaire where num_news="'.$donnee['forum'].'"');
								$ligne = $res2->fetch();
								echo '<p>'.$donnee['texte'].'</p>';
								echo '<a class="lienCom" href="forumTopic.php?num_news='.$donnee['forum'].'">'.$ligne[0].' message'.((intval($ligne[0]) == 1)?'':'s').'</a></div>';
							}
							$res2->closeCursor();
						}
						$resultat->closeCursor();
					?>
				</div>
			</div>
		</div>
		
		<?php include("piedPage.php"); ?>
		
	</body>
</html>