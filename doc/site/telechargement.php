<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta name="author" content="Lecoconnier David" />
		<meta name="category" content="Logiciel" />
		<meta name="language" content="fr" />
		<meta name="description" content="R&eacute;cup&eacute;rez sur cette page la derni&egrave;re version de Fu(X), le lecteur audio simple, l&eacute;ger et sans concession !" />
		<meta name="keywords" content="Fux, Fu(X), Fux 2.0, fix, fyx, fixplay, fuc, musique, rapide, simple, lecteur, audio, mp3, m3u, tag, liste, gestion, interface, claire, efficace, explorateur, glisser, d&eacute;poser" />
		<meta name="robots" content="all" />
		<meta http-equiv="content-language" content="french" />
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - T&eacute;l&eacute;chargement</title>
		<link rel="stylesheet" type="text/css" href="./Styles/style.css" media="screen" />
		<link rel="icon" type="image/png" href="images/play.png" />
	</head>
	<body>
		<?php
			include("menu.php");
			require("bdd.php");
		?>
		
		<div id="corps">
			<?php $page_actuelle='telechargement.php'; include("droite.php"); ?>
			<div id="milieu">
				<div id="download">
					<h3>T&eacute;l&eacute;chargement</h3>										<p>Vous avez deux possibilit&eacute;s : soit vous t&eacute;l&eacute;charger une version ci-dessous ou bien vous vous rendez sur la page du <a id="depot" href="https://github.com/etrange02/Fux.git">d&eacute;p&ocirc;t</a>.</p>
					<?php						
						if (isset($_GET['plus']))
						{
							$requete = 'SELECT * FROM version ORDER BY parution DESC';
							$resultatTout = $bdd->query($requete);
							
							if ($resultatTout->rowCount() == 0)
								echo '<p>Aucune version disponible.</p>';
							else
							{
								while ($ligneTout = $resultatTout->fetch())
								{
									echo '<div class="info">';
										echo '<h4>Fu(X) 2.0 '.$ligneTout['version'].'</h4>';
										echo '<p>'.htmlentities($ligneTout['nom']).' : <a href="./'.$ligneTout['lien'].'">lien</a></p>';
										//echo '<p>Fu(X) 2.0 '.$ligneTout['version'].' - '.$ligneTout['nom'].' : <a href="./telechargement/'.$ligneTout['lien'].'">lien</a></p>';
									echo '</div>';
								}
							}
							$resultatTout->closeCursor();
						}
						else
						{
							$requete = 'SELECT * FROM version ORDER BY id DESC LIMIT 0, 1';
							$resultat = $bdd->query($requete);
							
							if ($resultat->rowCount() == 0)
								echo '<p>Aucune version disponible.</p>';
							else
							{
								$ligne = $resultat->fetch();
								$ver = $ligne['version'];
								$resultat->closeCursor();
								
								$requete = 'SELECT * FROM version WHERE version=\''.$ver.'\'';
								$resultat = $bdd->query($requete);
								
								while ($donnee = $resultat->fetch())
								{
									echo '<div class="info">';
										echo '<h4>Fu(X) 2.0 '.$donnee['version'].'</h4>';
										echo '<p>'.htmlentities($donnee['nom']).' : <a href="./'.$donnee['lien'].'">lien</a></p>';
										//echo '<p>Fu(X) 2.0 '.$donnee['version'].' - '.$donnee['nom'].' : <a href="./telechargement/'.$donnee['lien'].'">lien</a></p>';
									echo '</div>';
								}
							}
							$resultat->closeCursor();
							
							?>
							<form method="get" action="telechargement.php">
								<p>
									<input type="hidden" name="plus" value="on" />
									<input type="submit" value="Afficher tous les fichiers disponibles" />
								</p>
							</form>
							<?php
						}
					?>
				</div>
			</div>
		</div>
		
		<?php include("piedPage.php"); ?>
		
	</body>
</html>