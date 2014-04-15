<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta name="author" content="Lecoconnier David" />
		<meta name="category" content="Logiciel" />
		<meta name="language" content="fr" />
		<meta name="description" content="Participez &agrave; l'am&eacute;lioration de Fu(X) en d&eacute;posant vos messages !" />
		<meta name="keywords" content="Fux, Fu(X), Fux 2.0, fix, fyx, fixplay, fuc, musique, rapide, simple, lecteur, audio, mp3, m3u, tag, liste, gestion, interface, claire, efficace, explorateur, glisser, d&eacute;poser" />
		<meta name="robots" content="all" />
		<meta http-equiv="content-language" content="french" />
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Commentaire</title>
		<link rel="stylesheet" type="text/css" href="./Styles/style.css" media="screen" />
		<link rel="icon" type="image/png" href="images/play.png" />
	</head>
	<body>		
		<?php
			include("menu.php");
			require("bdd.php");
			
			$num_news = 0;
			$afficheAjoutCom = false;
			if (isset($_GET['num_news']))
				$num_news = intval($_GET['num_news']);
		?>
		
		<div id="corps">
			<?php $page_actuelle='commentaire.php?num_news='.$num_news; include("droite.php"); ?>
			<div id="milieu">
				<div id="actu">
				<?php
					echo '<h3>News n&deg;'.$num_news.'</h3>';
					
					if ($num_news == 0)
					{
						echo '<p>Impossible d\'afficher les messages attach&eacute;s &agrave; cette news</p>';
					}
					else
					{						
						$resultat = $bdd->query('SELECT * FROM news WHERE id="'.$num_news.'"');
						$ligne = $resultat->fetch();
						if (!$ligne)
						{
							echo '<p>Erreur, la news demand&eacute;e n\'existe pas !</p>';
						}
						else
						{
							$resultat = $bdd->query('SELECT COUNT(*) FROM commentaire where num_news="'.$num_news.'"');
							$ligne = $resultat->fetch();
							$resultat->closeCursor();
							$afficheAjoutCom = true;
							
							if ($ligne[0] == 0)								
								echo '<p>Aucun message.</p>';
							else
							{						
								$resultat = $bdd->query('SELECT id, pseudo, texte FROM commentaire WHERE num_news="'.$num_news.'" ORDER BY id ASC');
								
								echo '<table id="commentaire">';
								
								while($donnee = $resultat->fetch())
								{
									$res2 = $bdd->query('SELECT pseudo, site, citation FROM utilisateur where id="'.$donnee['pseudo'].'"');
									$ligne = $res2->fetch();
									
									echo '<tr><td class="pseudo">'.$ligne['pseudo'];
									echo (!empty($ligne['site']) ? '<br /><a href="'.$ligne['site'].'">site</a></td>' : '</td>');
									echo '<td class="message">'.$donnee['texte'];
									echo (!empty($ligne['citation']) ? '<br /><br /><hr />'.$ligne['citation'].'</td></tr>' : '<br /><br /></td></tr>');
									$res2->closeCursor();
								}
								echo '</table>';
							}
							$resultat->closeCursor();
						}
						if ($afficheAjoutCom && isset($_SESSION['autorise']) && $_SESSION['autorise'])
						{
							?>
							<form action="commentaire_post.php" method="post" id="postMessage">
								<fieldset>
									<legend>Laisser un commentaire</legend>
									<table>
										<?php /*<tr>
											<td><label for="idpseudo">Pseudo</label></td>
											<td><input type="text" id="idpseudo" name="pseudo" maxlength="255" size="30" value="<?php if (!empty($_SESSION['pseudo'])) echo $_SESSION['pseudo'];?>" /></td>
										</tr>
										<tr>
											<td><label for="idmdp">Mot de passe</label></td>
											<td><input type="password" id="idmdp" name="mdp" maxlength="255" size="30" value="<?php if (!empty($_SESSION['mdp'])) echo $_SESSION['mdp'];?>" /></td>
										</tr>*/ ?>
										<tr>
											<td><label for="idcom">Commentaire</label></td>
											<td><textarea id="idcom" name="commentaire" rows="4" cols="45" ></textarea></td>
										</tr>
										<tr>
											<td></td>
											<td><input type="submit" value="Poster" /><input type="hidden" name="num_news" value="<?php echo $num_news; ?>" /></td>
										</tr>
									</table>
								</fieldset>
							</form>
							<br /><br />
							<?php
							/*<form action="inscription.php" method="post" id="postInscription">
								<p>Si vous n'&ecirc;tes pas inscrit, vous pouvez vous <input type="submit" value="inscrire ici." />
								<input type="hidden" name="num_news" value="<?php echo $num_news; ?>" /></p>
							</form>*/
							
						}
					}
				?>
				</div>
			</div>
		</div>
		
		<?php include("piedPage.php"); ?>
		
	</body>
</html>