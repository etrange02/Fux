<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta name="author" content="Lecoconnier David" />
		<meta name="category" content="Logiciel, Explorateur" />
		<meta name="language" content="fr" />
		<meta name="description" content="Page associ&eacute; &agrave; mon compte. Fu(X) est un lecteur de musique &agrave; l'interface simple. Il lit les mp3 et g&egrave;re les tags. Fu(X) permet d'acc&eacute;der tr&egrave;s facilement &agrave; ses dossiers et titre gr&acirc;ce &agrave; son double explorateur de dossier !" />
		<meta name="keywords" content="Fux, Fu(X), Fux 2.0, fix, fyx, fixplay, fuc, musique, rapide, simple, lecteur, audio, mp3, m3u, tag, liste, gestion, interface, claire, efficace, explorateur, glisser, d&eacute;poser" />
		<meta name="robots" content="all" />
		<meta http-equiv="content-language" content="french" />
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Mon compte</title>
		<link rel="stylesheet" type="text/css" href="./Styles/style.css" media="screen" />
		<link rel="icon" type="image/png" href="images/play.png" />
	</head>
	<body>
		<?php
			include("menu.php");
			require("bdd.php");
		?>
		
		<div id="corps">
			<?php $page_actuelle='index.php'; include("droite.php"); ?>
			<div id="milieu">
				<div id="actu">					
					<?php
						if (!empty($_SESSION['pseudo']) && !empty($_SESSION['mdp']))
						{
							$requete = 'SELECT * FROM utilisateur WHERE id=\''.$_SESSION['idpseudo'].'\'';
							$resultat = $bdd->query($requete);
							$utilisateur = $resultat->fetch();
							
							echo '<h3>'.$_SESSION['pseudo'].', mes informations</h3>';
							?>
								<ul>
									<li><a href="compte.php?pass=on">Modifier mon mot de passe</a></li>
									<li><a href="compte.php?sign=on">Modifier ma signature</a></li>
									<li><a href="compte.php?mail=on">Modifier mon mail</a></li>
									<li><a href="compte.php?site=on">Modifier mon site</a></li>
									<li><a href="compte.php?news=on">Recevoir les newsletters</a></li>
								</ul>
							<?php
							
							if (isset($_GET['pass']))
							{
								if (isset($_POST['savePass']))
								{
									if (!empty($_POST['anc']) && !empty($_POST['pass1']) && !empty($_POST['pass2']))
									{
										$mdp = htmlentities($_POST['pass1'], ENT_QUOTES, 'UTF-8');
										$mdp2 = htmlentities($_POST['pass2'], ENT_QUOTES, 'UTF-8');
										$pass = htmlentities($_POST['anc'], ENT_QUOTES, 'UTF-8');
										
										if (strcmp($pass, $utilisateur['mdp']) == 0)
										{
											if (strcmp($mdp, $mdp2) == 0)
											{
												$requete = 'UPDATE utilisateur SET mdp=\''.$mdp.'\' WHERE id=\''.intval($_SESSION['idpseudo']).'\'';
												//$requete = 'INSERT INTO utilisateur(pseudo, mdp, admin, site) VALUES (\''.$pseudo.'\', \''.$mdp.'\', 0, \''.$site.'\', \''.$citation.'\', '.$newsletter.')';
												if ($bdd->exec($requete))
												{
													echo '<p>Modification faite.</p>';
													$_SESSION['mdp'] = $mdp;
												}
												else
													echo '<p>Impossible de modifier votre mot de passe.</p>';
											}
											else
												echo '<p>Erreur, vous n\'avez pas saisi deux fois votre nouveau mot de passe.</p>';
										}
										else
											echo '<p>Erreur, votre ancien mot de passe ne correspond pas au mot de passe que vous utilisez pour vous connecter.</p>';
									}
									else
										echo '<p>Erreur, aucun mot de passe n\'a &eacute;t&eacute; donn&eacute; !</p>';
								}
								else
								{
									?>
									<form id="formModif" action="compte.php?pass=on" method="post">
										<fieldset>
											<legend>Modifier mon mot de passe</legend>
											<table>
												<tr><td><label for="idAnc">Ancien MdP</label></td><td><input type="password" id="idAnc" name="anc" size="100" maxlength="255" /></td></tr>
												<tr><td><label for="idpass1">Nouveau MdP</label></td><td><input type="password" id="idpass1" name="pass1" size="100" maxlength="255" /></td></tr>
												<tr><td><label for="idpass2">Nouveau MdP (bis)</label></td><td><input type="password" id="idpass2" name="pass2" size="100" maxlength="255" /></td></tr>
												<tr><td></td><td><input type="submit" name="Modifier" /><input type="hidden" name="savePass" /></td></tr>
											</table>
										</fieldset>
									</form>
									<?php
								}
							}
							else if (isset($_GET['sign']))
							{
								if (isset($_POST['saveSign']))
								{
									$signature = nl2br(htmlentities($_POST['signature'], ENT_QUOTES, 'UTF-8'));
									
									$requete = 'UPDATE utilisateur SET citation=\''.$signature.'\' WHERE id=\''.intval($_SESSION['idpseudo']).'\'';
									//$requete = 'INSERT INTO utilisateur(pseudo, mdp, admin, site) VALUES (\''.$pseudo.'\', \''.$mdp.'\', 0, \''.$site.'\', \''.$citation.'\', '.$newsletter.')';
									if ($bdd->exec($requete))
										echo '<p>Signature modifi&eacute;e !</p>';
									else
										echo '<p>Impossible de modifier votre signature.</p>';
								}
								else
								{
									if(empty($utilisateur['citation']))
										echo '<p>Vous n\'avez pas de signature.</p>';
									else
										echo '<p>Voici votre signature actuelle :<br /><div id="cadre">'.$utilisateur['citation'].'</div></p>';
									?>
									<p>Attention, les balises html ont &eacute;t&eacute; d&eacute;sactiv&eacute;es !</p>
									<form id="formModif" action="compte.php?sign=on" method="post">
										<fieldset>
											<legend>Modifier ma signature</legend>
											<table>
												<tr><td><label for="idSign">Ma signature</label></td></tr>
												<tr><td><textarea id="idSign" name="signature" cols="100" rows="6"></textarea></td></tr>
												<tr><td><input type="submit" name="Modifier" /><input type="hidden" name="saveSign" /></td></tr>
											</table>
										</fieldset>
									</form>
									<?php
								}
							}
							else if (isset($_GET['mail']))
							{
								if (isset($_POST['saveMail']))
								{
									if (!empty($_POST['mail']))
									{
										$mail = htmlentities($_POST['mail'], ENT_QUOTES, 'UTF-8');
										if (preg_match('#^[\w.-]+@[\w.-]+\.[a-zA-Z]{2,6}$#', $mail)) // Test si le mail est valide dans la forme
										{
											$requete = 'UPDATE utilisateur SET mail=\''.$mail.'\' WHERE id=\''.intval($_SESSION['idpseudo']).'\'';
											//$requete = 'INSERT INTO utilisateur(pseudo, mdp, admin, site) VALUES (\''.$pseudo.'\', \''.$mdp.'\', 0, \''.$site.'\', \''.$citation.'\', '.$newsletter.')';
											if ($bdd->exec($requete))
												echo '<p>Modification faite.</p>';
											else
												echo '<p>Impossible d\'enregistrer.</p>';
										}
										else
											echo '<p>Mail invalide.</p>';
									}
									else
										echo '<p>Erreur, aucun mail n\'a &eacute;t&eacute; donn&eacute; !</p>';
								}
								else
								{
									echo '<p>Actuellement, votre mail est : '.$utilisateur['mail'].'</p>';
									?>
									<form id="formModif" action="compte.php?mail=on" method="post">
										<fieldset>
											<legend>Mon adresse mail</legend>
											<label for="idMail">Mail</label>
											<input type="text" id="idMail" name="mail" size="100" maxlength="255" />
											<input type="submit" name="Enregistrer" />
											<input type="hidden" name="saveMail" />
										</fieldset>
									</form>
									<?php
								}
							}
							else if (isset($_GET['site']))
							{
								if (isset($_POST['saveWeb']))
								{
									if (!empty($_POST['site']))
									{
										$site = htmlentities($_POST['site'], ENT_QUOTES, 'UTF-8');
										if (preg_match('#http://+[\w.-]+\.[a-zA-Z]{2,6}$#', $site)) // Test si le site est valide dans la forme
										{
											$requete = 'UPDATE utilisateur SET site=\''.$site.'\' WHERE id=\''.intval($_SESSION['idpseudo']).'\'';
											//$requete = 'INSERT INTO utilisateur(pseudo, mdp, admin, site) VALUES (\''.$pseudo.'\', \''.$mdp.'\', 0, \''.$site.'\', \''.$citation.'\', '.$newsletter.')';
											if ($bdd->exec($requete))
												echo '<p>Modification faite.</p>';
											else
												echo '<p>Impossible d\'enregistrer.</p>';
										}
										else
											echo '<p>Lien invalide. V&eacute;rifiez qu\'il commence bien par http://.</p>';
									}
									else
										echo '<p>Erreur, aucun lien n\'a &eacute;t&eacute; donn&eacute; !</p>';
								}
								else
								{
									if (empty($utilisateur['site']))
										echo 'Aucun site n\'a &eacute;t&eacute; enregistr&eacute;.';
									else
										echo '<p>Actuellement, votre site est : '.$utilisateur['site'].'</p>';
									?>
									<form id="formModif" action="compte.php?site=on" method="post">
										<fieldset>
											<legend>Mon site web</legend>
											<label for="idLien">Lien</label>
											<input type="text" id="idLien" name="site" size="100" maxlength="255" title="Le lien doit commencer par http:// !" />
											<input type="submit" name="Enregistrer" />
											<input type="hidden" name="saveWeb" />
										</fieldset>
									</form>
									<?php
								}
							}
							else if (isset($_GET['news']))
							{
								if (isset($_POST['saveNews']))
								{
									$news = isset($_POST['news']);
									$requete = 'UPDATE utilisateur SET newsletter=\''.$news.'\' WHERE id=\''.intval($_SESSION['idpseudo']).'\'';
									//$requete = 'INSERT INTO utilisateur(pseudo, mdp, admin, site) VALUES (\''.$pseudo.'\', \''.$mdp.'\', 0, \''.$site.'\', \''.$citation.'\', '.$newsletter.')';
									if ($bdd->exec($requete))
										echo '<p>Modification faite.</p>';
									else
										echo '<p>Impossible d\'enregistrer la modification.</p>';
								}
								else
								{
									?>
									<form id="formModif" action="compte.php?news=on" method="post">
										<fieldset>
											<legend>La newsletter</legend>
											<input type="checkbox" id="idNews" name="news" <?php if ($utilisateur['newsletter']) echo 'checked="checked"'; ?> />
											<label for="idNews">Je souhaite &ecirc;tre inform&eacute; des nouveaut&eacute;s</label>											
											<input type="submit" name="Enregistrer" />
											<input type="hidden" name="saveNews" />
										</fieldset>
									</form>
									<?php
								}
							}
							
							$resultat->closeCursor();
						}
						else
							echo 'Erreur, vous devez vous connecter pour acc&eacute;der &agrave; ces informations.';
					?>
				</div>
			</div>
		</div>
		<?php include("piedPage.php"); ?>		
	</body>
</html>