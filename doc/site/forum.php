<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta name="author" content="Lecoconnier David" />
		<meta name="category" content="Logiciel, Explorateur" />
		<meta name="language" content="fr" />
		<meta name="description" content="Forum de Fu(X). Fu(X) est un lecteur de musique &agrave; l'interface simple. Il lit les mp3 et g&egrave;re les tags. Fu(X) permet d'acc&eacute;der tr&egrave;s facilement &agrave; ses dossiers et titre gr&acirc;ce &agrave; son double explorateur de dossier !" />
		<meta name="keywords" content="Fux, Fu(X), Fux 2.0, fix, fyx, fixplay, fuc, musique, rapide, simple, lecteur, audio, mp3, m3u, tag, liste, gestion, interface, claire, efficace, explorateur, glisser, d&eacute;poser" />
		<meta name="robots" content="all" />
		<meta http-equiv="content-language" content="french" />
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Forum</title>
		<link rel="stylesheet" type="text/css" href="./Styles/style.css" media="screen" />
		<link rel="icon" type="image/png" href="images/play.png" />
	</head>
	<body>
		<?php
			include("menu.php");
			require("bdd.php");
		?>
		
		<div id="corps">
			<?php $page_actuelle='forum.php'; include("droite.php"); ?>
			<div id="milieu">
				<div id="actu">
					<h3>Forum</h3>
					<?php
						$requete = 'SELECT * FROM forum ORDER BY modification DESC LIMIT 0, 20';
						$resultat = $bdd->query($requete);
						
						if (isset($_SESSION['autorise']) && $_SESSION['autorise'])
						{
							?>
							<form action="forum_nouveau.php" method="post" id="forumNouveau"><!--forum_nouveau.php-->
								<p>
									<input type="submit" value="Cr&eacute;er un sujet" />
								</p>
							</form>
							<?php
						}
						
						if ($resultat->rowCount() == 0)
							echo "<p>Aucun forum n'existe pour le moment.</p>";
						else
						{
							$res2 = 0;
							$i = 0;
							echo '<table id="forum">';
							while($forum = $resultat->fetch())
							{
								$res2 = $bdd->query('SELECT * FROM utilisateur where id="'.$forum['auteur'].'"');
								$utilisateur = $res2->fetch();
								//echo '<div class="info"><h4>'.$forum['titre'].' <span class="auteur">par '.$utilisateur['pseudo'].' le '.$forum['date'].'</span></h4>';
								
								$res2 = $bdd->query('SELECT COUNT(*) FROM commentaire where num_news="'.$forum['id'].'"');
								$ligne = $res2->fetch();
								
								echo '<tr';
								echo (($i%2 == 0) ? ' class="gris"' : '');
								echo '><td><a href="forumTopic.php?num_news='.$forum['id'].'">'.$forum['titre'].'</a></td><td>'.$utilisateur['pseudo'].'</td><td>'.$ligne[0].' message'.((intval($ligne[0]) == 1)?'':'s').'</td></tr>';
								$i++;
								//echo '<tr><td '.( if($i%2==0)'class="gris"').'><a href="commentaire.php?num_news='.$forum['id'].'">'..'</a>';
							}
							echo '</table>';
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