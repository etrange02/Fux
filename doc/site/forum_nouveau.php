<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta name="author" content="Lecoconnier David" />
		<meta name="category" content="Logiciel, Explorateur" />
		<meta name="language" content="fr" />
		<meta name="description" content="Forum de Fu(X). Fu(X) est un lecteur de musique &agrave; l'interface simple. Il lit les mp3 et g&egrave;re les tags. Fu(X) permet d'acc&eacute;der tr&egrave;s facilement &agrave; ses dossiers et titre gr&acirc;ce &agrave; son double explorateur de dossier !" />
		<meta name="keywords" content="Fu(X), Fu(X) 2.0, 2.0, Fux, musique, rapide, simple, lecteur, audio, mp3, m3u, tag, liste, gestion, interface, claire, efficace, explorateur, glisser, d&eacute;poser" />
		<meta name="robots" content="all" />
		<meta http-equiv="content-language" content="french" />
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Forum - Cr&eacute;er un Sujet</title>
		<link rel="stylesheet" type="text/css" href="./Styles/style.css" media="screen" />
		<link rel="icon" type="image/png" href="images/play.png" />
	</head>
	<body>
		<?php
			include("menu.php");
			require("bdd.php");
			require("admin/fonction.php");
		?>
		
		<div id="corps">
			<?php $page_actuelle='forum_nouveau.php'; include("droite.php"); ?>
			<div id="milieu">
				<div id="actu">
					<h3>Forum - Cr&eacute;er un Sujet</h3>
					<?php
						if (isset($_SESSION['autorise']) && $_SESSION['autorise'])
						{
							$affiche = false;
							$_titre = isset($_POST['titre']) && !empty($_POST['titre']);
							$_message = isset($_POST['message']) && !empty($_POST['message']);
							$titre = '';
							$message = '';
							
							if ($_titre)
								$titre = utf8tohtml($_POST['titre'], true);
							if ($_message)
								$message = nl2br(utf8tohtml($_POST['message'], true));
								
							if (isset($_POST['creer']) && $_titre && $_message)
							{
								$requete = 'INSERT INTO forum(auteur, titre, ferme, modification) VALUES ('.$_SESSION['idpseudo'].', \''.$titre.'\', 0, NOW())';
								if ($bdd->exec($requete))
								{
									$identifiant = $bdd->lastInsertId('id');
									$requete = 'INSERT INTO commentaire(num_news, pseudo, date, texte) VALUES (\''.$identifiant.'\', \''.$_SESSION['idpseudo'].'\', NOW(), \''.$message.'\')';
									if ($bdd->exec($requete))
										header('Location: forumTopic.php?num_news='.$identifiant.'.php');
									else
										echo '<p>Une erreur a emp&ecirc;ch&eacute; l\'ajout du sujet. Veuillez contacter un administrateur fux@fuxplay.com.</p>';
								}
								else
									echo '<p>Une erreur a emp&ecirc;ch&eacute; l\'ajout du sujet. Veuillez contacter un administrateur fux@fuxplay.com.</p>';
							}
							else
								$affiche = true;
							
							if ($affiche)
							{
								?>
								<p>Veuillez remplir les champs en rouge.</p>
								<form action="<?php $PHP_SELF;?>" method="post" id="creerSujet">
									<p>
									<table>
										<tr>
											<td><label for="idTitre" <?php if (!$_titre) echo 'class="rouge"'; ?>>Titre</label></td>
											<td><input type="text" id="idTitre" name="titre" maxlength="255" size="75" <?php if (isset($_POST['creer'])) echo 'value="'.$titre.'"'; ?> /></td>
										</tr>
										<tr>
											<td><label for="idMessage" <?php if (!$_message) echo 'class="rouge"'; ?>>Message</label></td>
											<td><textarea id="idMessage" name="message" rows="7" cols="100"><?php if (isset($_POST['creer'])) echo $message; ?></textarea></td>
										</tr>
										<tr>
											<td></td>
											<td><input type="submit" value="Cr&eacute;er le sujet" name="creer" /></td>
										</tr>
									</table>
									</p>
								</form>
								<?php
							}
						}
						else
							header('Location: index.php');
					?>
				</div>
			</div>
		</div>
		
		<?php include("piedPage.php"); ?>
		
	</body>
</html>