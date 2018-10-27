//
// Book : chapitres 12, 13, 14 & 15 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 04/03/2018 - Installation FLTK 1.3.4-2 (http://www.fltk.org) [conseils d'installation du site bumpyroadtocode.com car la librairie utilisée par BS, 1.1.x, était très ancienne]
// Commit en cours : 20/04/2018 - exos chapitre 15
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

#include "Graph.h"
#include "Simple_window.h"

// Drill page 546
int fac(int n) { return n > 1 ? n * fac(n - 1) : 1; }	// Fonction factorielle récursive (page 548)

double one(double) noexcept { return 1; }
double slope(double x) noexcept { return x / 2; }
double square(double x) noexcept { return x * x; }
double sloping_cos(double x) noexcept { return cos(x) + slope(x); }
double term(double x, int n) noexcept { return pow(x, n) / fac(n); }
double expe(double x, int n) noexcept
{
	double sum = 0;
	for (int i = 0; i < n; ++i) sum += term(x, i);
	return sum;
}

// Exo 4 & 5 page 548
double sin_ex4(double x) noexcept { return sin(x); }
double cos_ex4(double x) noexcept { return cos(x); }
double sum_ex4(double x) noexcept { return sin(x) + cos(x); }
double sum2_ex4(double x) noexcept { return sin(x)*sin(x) + cos(x)*cos(x); }



int main()
{

	using namespace Graph_lib;	// Le préfixe Graph_Lib : le namespace ne semble pas fonctionner tout le temps !!! Ambiguïté avec les nouvelles librairies FLTK ?

	// ************************************************************************************************************************************************************
	// Constantes : Drill pages 546 & 547
	constexpr int xmax = 600;
	constexpr int ymax = 600;

	constexpr int x_orig = xmax / 2;
	constexpr int y_orig = ymax / 2;
	const Point orig{ x_orig ,y_orig };

	constexpr double r_min = -10;
	constexpr double r_max = 11;

	constexpr int n_points = 400;

	constexpr double x_scale = 20;
	constexpr double y_scale = 20;

	const Point t15{ 600, 200 };

	// Exos 6, 7 & 8 page 548
	Simple_window chap15c_win(t15, xmax, ymax, "Bar Graph");	 // Inclut un bouton Next qui permet une pause

	// Ouverture en lecture d'un fichier pour récupérer des données (2 champs : valeur et label)
	// Amélioration : tester la présence d'un label ou pas, valeurs double, etc.
	//string filename15 = "heights.txt";
	string filename15 = "production.txt";
	ifstream ist15{ filename15 };
	ist15.exceptions(ist15.exceptions() | ios_base::badbit);
	if (!ist15)error("Impossible d'ouvrir le fichier ", filename15);

	string str15_val{}, str15_lab{};
	vector <int> bg{};
	vector <string> bg_labels{};
	while (ist15 >> str15_val >> str15_lab) {
		bg.push_back(stoi(str15_val));
		bg_labels.push_back(str15_lab);

	}
	ist15.close();	// Fermeture du fichier

	ostringstream ss_bg;
	ss_bg << "Production de nickel dans le monde en 2017 (" << bg.size() << " valeurs)";
	chap15c_win.set_label(ss_bg.str());
	Bar_graph bg1{ bg,bg_labels, xmax, ymax, "pays", "tonnes" };
	bg1.set_color(Color::black);
	chap15c_win.attach(bg1);

	chap15c_win.wait_for_button();

	// Drill pages 546 & 547
	Simple_window chap15_win(t15, xmax, ymax, "Function graphs");	 // Inclut un bouton Next qui permet une pause

	// Axes
	Axis xa15{ Axis::x,Point{ 100,300 },400,20,"1 == 20 pixels" };
	xa15.set_color(Color::red);
	chap15_win.attach(xa15);

	Axis ya15{ Axis::y,Point{ 300,500 },400,20,"1 == 20 pixels" };
	ya15.set_color(Color::red);
	chap15_win.attach(ya15);

	Fct_stored s{ one,r_min,r_max,orig,n_points,x_scale,y_scale };	// On a remplacé les 5 "Function" de s à s5 par "Fct_stored" qui stocke les paramètres
	s.set_color(Color::black);
	chap15_win.attach(s);

	Fct_stored s2{ slope,r_min,r_max,orig,n_points,x_scale,y_scale };
	s2.set_color(Color::black);
	chap15_win.attach(s2);

	Text ts2{ Point{100,y_orig + y_orig / 2 - 20},"x/2" };
	ts2.set_color(Color::black);
	chap15_win.attach(ts2);

	Fct_stored s3{ square,r_min,r_max,orig,n_points,x_scale,y_scale };
	s3.set_color(Color::black);
	chap15_win.attach(s3);

	Fct_stored s4{ [](double x)-> double {return cos(x); }, r_min,r_max,orig,n_points,x_scale,y_scale };
	s4.set_color(Color::blue);
	chap15_win.attach(s4);

	Fct_stored s5{ sloping_cos,r_min,r_max,orig,n_points,x_scale,y_scale };
	s5.set_color(Color::dark_yellow);
	chap15_win.attach(s5);

	for (int n = 0; n < 50; ++n) {	// Page 533
		ostringstream ss;
		ss << "Approximation exponentielle; n = " << n;
		chap15_win.set_label(ss.str());
		Fct_stored exponentielle{ [n](double x) {return expe(x,n); },r_min,r_max,orig,200,x_scale,y_scale };	// Cet objet ne se crée pas avec Function (problème de matching de type) mais parfaitement avec la nouvelle Fct_stored
		chap15_win.attach(exponentielle);
		chap15_win.wait_for_button();
		chap15_win.detach(exponentielle);
	}

	chap15_win.wait_for_button();

	// Exo 4 page 548
	Simple_window chap15b_win(t15, xmax, ymax, "Exo 4 page 548");	 // Inclut un bouton Next qui permet une pause

	Axis xa15_b{ Axis::x,Point{ 100,300 },400,20,"1 == 20 pixels" };
	xa15_b.set_color(Color::red);
	chap15b_win.attach(xa15_b);

	Axis ya15_b{ Axis::y,Point{ 300,500 },400,20,"1 == 20 pixels" };
	ya15_b.set_color(Color::dark_magenta);
	chap15b_win.attach(ya15_b);

	Fct_stored se4_1{ sin_ex4,r_min,r_max,orig,n_points,x_scale,y_scale };
	se4_1.set_color(Color::black);
	chap15b_win.attach(se4_1);

	Fct_stored se4_2{ cos_ex4,r_min,r_max,orig,n_points,x_scale,y_scale };
	se4_2.set_color(Color::red);
	chap15b_win.attach(se4_2);

	Fct_stored se4_3{ sum_ex4,r_min,r_max,orig,n_points,x_scale,y_scale };
	se4_3.set_color(Color::yellow);
	chap15b_win.attach(se4_3);

	Fct_stored se4_4{ sum2_ex4,r_min,r_max,orig,n_points,x_scale,y_scale };
	se4_4.set_color(Color::blue);
	chap15b_win.attach(se4_4);

	chap15b_win.wait_for_button();



	// ***********************************************************************************************************************************************************
	// Exercices page 484, 485 & 516, 517

	// Exercice 10 page 517 
	const Point tl_pw{ 600, 200 };
	Simple_window Pseudo_window(tl_pw, 1200, 800, "Exercice n°10, page 517");	 // Inclut un bouton Next qui permet une pause

	// Coins ronds de la fenêtre
	Graph_lib::Box b_pw{ Point{ 0,30 },1199,769,"" };
	b_pw.set_color(Color::dark_yellow);
	Pseudo_window.attach(b_pw);

	// Label + control icons
	Graph_lib::Rectangle r_pw{ Point{ 0,60 },1200,5 };	// Rajout de Graph_Lib
	r_pw.set_fill_color(Color::dark_yellow);
	Pseudo_window.attach(r_pw);

	Text t_pw{ Point{ 20,50 },"Pseudo window de test" };
	t_pw.set_font(Font::times_bold_italic);
	t_pw.set_font_size(20);
	t_pw.set_color(Color::black);
	Pseudo_window.attach(t_pw);

	Graph_lib::Rectangle multi_box1_pw{ Point{ 1140,45 },10,10 };
	multi_box1_pw.set_color(Color::black);
	Pseudo_window.attach(multi_box1_pw);

	Graph_lib::Rectangle multi_box2_pw{ Point{ 1145,40 },10,10 };
	multi_box2_pw.set_color(Color::black);
	Pseudo_window.attach(multi_box2_pw);

	Graph_lib::Rectangle baisser_pw{ Point{ 1120,50 },10,5 };
	baisser_pw.set_fill_color(Color::black);
	Pseudo_window.attach(baisser_pw);

	Mark m_pw{ Point{ 1180,50 },'x' };
	Pseudo_window.attach(m_pw);

	// Classe rajoutée Binary Tree : exo 11 page 517
	Binary_tree bt{ Point{ 600,100 },6, Binary_tree::carre };	// On trace un arbre binaire
	bt.set_color(Color::black);
	bt.set_fill_color(Color::yellow);
	bt.set_style(Line_style::dot);								// Style des traits (ex : dot, dash, solid)
	bt.nommer_noeud(5, 3, "Hello");								// On nomme un noeud - Exo 14 page 517
	Pseudo_window.attach(bt);

	Pseudo_window.wait_for_button();
	// ********************************************************************************************************************************************************

	// Fenêtre globale présentant les différents widgets testés
	const Point tl{ 600, 200 };
	Simple_window win(tl, 1200, 800, "Fenêtre globale présentant les différents widgets testés (chapitres 12, 13, 14)");	 // Inclut un bouton Next qui permet une pause

	// Classe rajoutée Smiley : exo 1 page 516
	Smiley sm{ Point{ 100,400 },50 };
	sm.set_color(Color::dark_red);
	win.attach(sm);

	// Classe rajoutée : exo 1 page 484
	Graph_lib::Arc a{ Point{ 20,20 },20,20,90,180 };
	a.set_color(Color::blue);
	win.attach(a);

	// Classe rajoutée : exo 2 page 484
	// Graph_lib::Box b{ Point{ 500,650 },200,100,"" };
	// b.set_color(Color::blue);
	// win.attach(b);

	// Classe rajoutée : exo 3 page 484
	Graph_lib::Arrow f{ Point{ 400,100 },Point{ 700,100 },true,true };
	f.set_color(Color::dark_green);
	win.attach(f);

	// Organigramme simplifié : exo 6 page 484
	// Amélioration : une classe organigramme avec un vecteur définissant les boites et leur connexion par niveau
	Graph_lib::Box org1{ Point{ 120,650 },90,40,"Window" };
	org1.set_color(Color::magenta);
	win.attach(org1);

	Graph_lib::Box org2{ Point{ 100,750 },140,40,"Simple Window" };
	org2.set_color(Color::magenta);
	win.attach(org2);

	Graph_lib::Arrow f1{ Point{ 170,690 },Point{ 170,750 },true,false };
	f1.set_color(Color::magenta);
	win.attach(f1);

	// Hexagone régulier - exo 8&9 page 484
	Vector_ref <Graph_lib::Regular_Hexagon>Reg_hexa{};

	for (int i = 0; i < 8; ++i)
	{

		Reg_hexa.push_back(new Graph_lib::Regular_Hexagon{ Point{ 50 + i * 50,150 },20 });
		Reg_hexa[i].set_fill_color(Color::red);
		win.attach(Reg_hexa[i]);

	}

	// Classe rajoutée du Triangle rectangle : exo 14 page 485
	Graph_lib::Triangle_Rectangle tr{ Point{ 350,700 },-100,100 };
	tr.set_color(Color::dark_green);
	win.attach(tr);

	// Classe rajoutée Etoile : exo 19 page 485
	Graph_lib::Etoile et{ Point{ 350,600 },50 };
	et.set_color(Color::dark_red);
	win.attach(et);

	// Classe rajoutée Immobile_Circle : exo 4 page 516
	Immobile_Circle c{ Point{ 300,100 },25 };
	c.move(20, 20);	// Rien ne se passe car la fonction move a été désactivée
	win.attach(c);

	// Classe rajoutée Striped_circle : exo 6 page 516
	Striped_circle sc{ Point{ 100,250 },50 };
	sc.set_color(Color::dark_yellow);
	win.attach(sc);

	// Classe rajoutée Regular_octogon : exo 8 page 516
	Regular_octogon ro{ Point{ 800,400 },50 };
	ro.set_color(Color::dark_yellow);
	ro.set_style(Line_style::dot);
	ro.set_fill_color(Color::white);
	ro.move(100, -300);
	win.attach(ro);



	// ***********************************************************************************************************************************************************
	// Exercices page 438 et 439

	// Classe rajoutée Striped_rectangle : exo 5 page 516
	Graph_lib::Striped_rectangle r{ Point{ 200,200 },100,30 };	// Rajout de Graph_Lib
	r.set_color(Color::blue);
	win.attach(r);
	Text t{ Point{ 230,220 },to_string(r.se().x) + "," + to_string(r.se().y) };	// On affiche le résultat de l'une des fonctions de l'exo 4 page 484
	t.set_color(Color::black);
	win.attach(t);

	Closed_polyline poly_rect;
	poly_rect.add(Point{ 100,50 });
	poly_rect.add(Point{ 200,50 });
	poly_rect.add(Point{ 200,100 });
	poly_rect.add(Point{ 100,100 });
	poly_rect.add(Point{ 50,75 });
	poly_rect.set_color(Color::red);
	win.attach(poly_rect);


	Open_polyline initialeA; // A
	initialeA.add(Point{ 400,50 });
	initialeA.add(Point{ 425,10 });
	initialeA.add(Point{ 450,50 });
	initialeA.add(Point{ 437,30 });
	initialeA.add(Point{ 412,30 });
	initialeA.set_color(Color::black);
	initialeA.set_style(Line_style(Line_style::solid, 4));
	win.attach(initialeA);

	Open_polyline initialeT; // T
	initialeT.add(Point{ 500,10 });
	initialeT.add(Point{ 550,10 });
	initialeT.add(Point{ 525,10 });
	initialeT.add(Point{ 525,50 });
	initialeT.set_color(Color::green);
	initialeT.set_style(Line_style(Line_style::solid, 4));
	win.attach(initialeT);

	// Tic Tac Toe : 9 cases *********************************************************************************************
	// Le stockage en vecteur permettant d'afficher facilement les 9 cases 

	Vector_ref <Graph_lib::Rectangle>ttt{};

	for (int i = 0; i < 3; ++i)
	{

		ttt.push_back(new Graph_lib::Rectangle{ Point{ 200 + i * 50,300 },50,50 });	// ligne 1 (explication de new en page 466)
		ttt.push_back(new Graph_lib::Rectangle{ Point{ 200 + i * 50,350 },50,50 });	// ligne 2
		ttt.push_back(new Graph_lib::Rectangle{ Point{ 200 + i * 50,400 },50,50 });	// ligne 3

	}

	for (int i = 0; i < 9; ++i)
	{
		if (i % 2) {							// En fonction du numéro du carré (pair ou impair), on change la couleur de fond
			ttt[i].set_fill_color(Color::white);
		}
		else {
			ttt[i].set_fill_color(Color::red);
		}
		win.attach(ttt[i]);
	}


	// La maison
	Graph_lib::Rectangle murs{ Point{ 400,230 },300,150 };	// Rajout de Graph_Lib
	murs.set_color(Color::black);
	win.attach(murs);

	Open_polyline toit;
	toit.add(Point{ 400,230 });
	toit.add(Point{ 550,180 });
	toit.add(Point{ 700,230 });
	toit.set_color(Color::black);
	win.attach(toit);

	Graph_lib::Rectangle porte{ Point{ 530,330 },40,50 };
	porte.set_color(Color::red);
	win.attach(porte);

	Circle bouton{ Point{ 560,360 },5 };
	bouton.set_fill_color(Color::cyan);
	win.attach(bouton);


	// Les 5 anneaux olympiques entrelacés : bleu, noir, rouge, jaune, vert
	Circle c1{ Point{ 500,500 },50 };
	c1.set_color(Color::blue);
	c1.set_style(Line_style(Line_style::solid, 4));
	win.attach(c1);

	Circle c2{ Point{ 575,500 },50 };
	c2.set_color(Color::black);
	c2.set_style(Line_style(Line_style::solid, 4));
	win.attach(c2);

	Circle c3{ Point{ 650,500 },50 };
	c3.set_color(Color::red);
	c3.set_style(Line_style(Line_style::solid, 4));
	win.attach(c3);

	Circle c4{ Point{ 537,550 },50 };
	c4.set_color(Color::yellow);
	c4.set_style(Line_style(Line_style::solid, 4));
	win.attach(c4);

	Circle c5{ Point{ 612,550 },50 };
	c5.set_color(Color::green);
	c5.set_style(Line_style(Line_style::solid, 4));
	win.attach(c5);


	// Photo commentée
	Image canard{ Point{ 800,480 },"canard.jpg" };
	win.attach(canard);
	Text t1{ Point{ 930,500 },"Le beau canard" };
	t1.set_font(Font::times_bold);
	t1.set_color(Color::black);
	t1.set_font_size(20);
	win.attach(t1);

	// Série de Polygones
	Graph_lib::Polygon poly_mult;							// Rajout de Graph_Lib 
	poly_mult.add(Point{ 200,600 });
	poly_mult.add(Point{ 100,600 });
	poly_mult.add(Point{ 100,500 });
	poly_mult.set_color(Color::dark_cyan);
	poly_mult.set_style(Line_style::solid);
	win.attach(poly_mult);
	//win.wait_for_button();

	poly_mult.add(Point{ 200,500 });
	win.attach(poly_mult);
	//win.wait_for_button();

	poly_mult.add(Point{ 300,550 });
	win.attach(poly_mult);
	//win.wait_for_button();


	// Parabole - f(x)=0.5x2 + 0,33x - 5
	Axis xa1{ Axis::x,Point{ 800,250 },400,10,"" };
	xa1.set_color(Color::black);
	win.attach(xa1);

	Axis ya1{ Axis::y,Point{ 1000,410 },400,10,"" };
	ya1.set_color(Color::black);
	win.attach(ya1);

	Lines courbe;														// On utilise l'objet Lines explicité en page 448, pour visualiser la courbe...
	for (double x = -5.0; x < 5.0; x += 0.1)
	{

		const double y = (1.0 / 2.0)*(x*x) + (1.0 / 3.0)*x - 5.0;

		const int coordx = static_cast<int>(round(1000 + x * 40));
		const int coordy = static_cast<int>(round(240 - y * 40));

		courbe.add(Point{ coordx,coordy }, Point{ coordx + 1,coordy });	//... sous la forme de petits traits d'un pixel de large

	}
	courbe.set_color(Color::red);
	win.attach(courbe);													// on affiche la "courbe" constituée des "points" définis dans la boucle
	win.wait_for_button();

	// DRILL page 483
	const Point tl1{ 0, 0 };
	Simple_window win_drill(tl1, 800, 1000, "Drill, page 483");	// Inclut un bouton Next qui permet une pause

	// Le grid 8x8
	Vector_ref <Graph_lib::Rectangle>grid_drill{};

	for (int i = 0; i < 8; ++i)
	{

		grid_drill.push_back(new Graph_lib::Rectangle{ Point{ 0 + i * 100,0 },100,800 });	// lignes verticales
		grid_drill.push_back(new Graph_lib::Rectangle{ Point{ 0,0 + i * 100 },800,100 });	// lignes horizontales

	}

	for (int i = 0; i < grid_drill.size(); ++i) { win_drill.attach(grid_drill[i]); }			// Affichage

	// Coloriser les rectangles de la diagonale
	Vector_ref <Graph_lib::Rectangle>diagonale_drill{};
	for (int i = 0; i < 8; ++i) { diagonale_drill.push_back(new Graph_lib::Rectangle{ Point{ 0 + i * 100,0 + i * 100 },100,100 }); }	// lignes verticales

	for (int i = 0; i < diagonale_drill.size(); ++i)
	{

		diagonale_drill[i].set_fill_color(Color::red);
		win_drill.attach(diagonale_drill[i]);	// Affichage

	}

	// 3 copies d'une image 200x200
	Vector_ref <Graph_lib::Image>part_of_duck{};
	for (int i = 0; i < 3; ++i) { part_of_duck.push_back(new Graph_lib::Image{ Point{ 0 + i * 200,600 },"canard.jpg" }); }

	for (int i = 0; i < part_of_duck.size(); ++i)
	{

		part_of_duck[i].set_mask(Point{ 0 + i * 30,0 + i * 20 }, 200, 200);
		win_drill.attach(part_of_duck[i]);	// Affichage

	}

	// Move d'une image 100x100 en diagonale
	Image chunck_of_duck{ Point{ 100 ,0  },"canard.jpg" };
	chunck_of_duck.set_mask(Point{ 60,40 }, 100, 100);
	win_drill.attach(chunck_of_duck);	// Affichage
	win_drill.wait_for_button();

	for (int i = 0; i < 6; ++i)
	{

		chunck_of_duck.move(100, 100);
		win_drill.wait_for_button();

	}


	// Exo 7 & 13 page 484&485 = RGB chart (255 possibilités)
	const Point tl2{ 100, 100 };
	Simple_window win_rgb(tl2, 800, 800, "RGB chart");	// Inclut un bouton Next qui permet une pause


	Vector_ref <Graph_lib::Rectangle>rgb_chart{};		// Le grid 8x8

	for (int c = 0; c < 16; ++c) {
		for (int l = 0; l < 16; ++l) { rgb_chart.push_back(new Graph_lib::Rectangle{ Point{ 0 + c * 20,0 + l * 20 },20,20 }); }

	}

	for (int i = 0; i < rgb_chart.size(); ++i) {
		rgb_chart[i].set_fill_color(i);
		win_rgb.attach(rgb_chart[i]);		// Affichage
	}

	win_rgb.wait_for_button();

	// Exercice 11 page 485
	const Point tl3{ 600, 200 };
	Simple_window win1(tl3, 1200, 800, "Exercice n°11, page 485");	// Inclut un bouton Next qui permet une pause

	Graph_lib::Ellipse e{ Point{ 500,400 },300,200 };
	e.set_color(Color::dark_red);
	win1.attach(e);

	Axis xa{ Axis::x,Point{ 300,400 },400,10,"" };
	xa.set_color(Color::black);
	win1.attach(xa);

	Axis ya{ Axis::y,Point{ 500,550 },300,10,"" };
	ya.set_color(Color::cyan);
	win1.attach(ya);

	Mark pf1{ Point{ 430,400 },'x' };
	win1.attach(pf1);

	Mark pf2{ Point{ 650,400 },'x' };
	win1.attach(pf2);

	Mark pe{ Point{ 500,200 },'x' };
	win1.attach(pe);

	Open_polyline foci_point;
	foci_point.add(Point{ 430,400 });
	foci_point.add(Point{ 500,200 });
	foci_point.add(Point{ 650,400 });
	foci_point.set_color(Color::blue);
	win1.attach(foci_point);


	// Exercice 12 page 485
	Circle cb{ Point{ 900,600 },100 };
	cb.set_color(Color::blue);
	win1.attach(cb);

	// On utilise les coordonnées polaires d'un point sur un cercle pour faire "bouger" la marque
	// x = a + R*cos angle 	y = b + R*sin angle (a et b étant les coordonnées du centre du cercle, R le rayon)
	// Attention : i est en radians (360° = 2PI Radians)
	for (double i = 0; i < 2 * PI; i += .2)
	{
		const int x_polaire = static_cast<int>(round(900 + 100 * cos(i)));
		const int y_polaire = static_cast<int>(round(600 + 100 * sin(i)));
		Mark px{ Point{ x_polaire,y_polaire },'x' };

		win1.attach(px);
		win1.wait_for_button();
	}

	/*
	// ***********************************************************************************************************************************************************
	// Drill de la page 437
	Point tl{100, 100 };
	Simple_window win(tl, 600, 400, "Ma première fenêtre");	// Inclut un bouton Next qui permet une pause
	win.set_label("Canvas n.1");
	win.wait_for_button();
	Axis xa{Axis::x,Point{20,300},280,10,"x axis" };
	win.attach(xa);
	win.set_label("Canvas n.2");
	win.wait_for_button();
	Axis ya{ Axis::y,Point{ 20,300 },280,10,"y axis" };
	ya.set_color(Color::cyan);
	ya.label.set_color(Color::dark_red);
	win.attach(ya);
	win.set_label("Canvas n.3");
	win.wait_for_button();
	Function sine{sin,0,100,Point{ 20,150 },1000,50,50 };
	sine.set_color(Color::blue);
	win.attach(sine);
	win.set_label("Canvas n.4");
	win.wait_for_button();
	Graph_lib::Polygon poly;							// Rajout de Graph_Lib
	poly.add(Point{ 300,200 });
	poly.add(Point{ 350,100 });
	poly.add(Point{ 400,200 });
	poly.set_color(Color::red);
	poly.set_style(Line_style::dash);
	win.attach(poly);
	win.set_label("Canvas n.5");
	win.wait_for_button();
	Graph_lib::Rectangle r{ Point{ 200,200 },100,50 };	// Rajout de Graph_Lib
	win.attach(r);
	win.set_label("Canvas n.6");
	win.wait_for_button();
	Closed_polyline poly_rect;
	poly_rect.add(Point{ 100,50 });
	poly_rect.add(Point{ 200,50 });
	poly_rect.add(Point{ 200,100 });
	poly_rect.add(Point{ 100,100 });
	poly_rect.add(Point{ 50,75 });
	win.attach(poly_rect);
	win.wait_for_button();
	r.set_fill_color(Color::yellow);
	poly.set_style(Line_style(Line_style::dash, 4));
	poly_rect.set_style(Line_style(Line_style::dash, 2));
	poly_rect.set_fill_color(Color::green);
	win.set_label("Canvas n.7");
	win.wait_for_button();
	Text t{ Point{ 100,150 },"hello, c'est beau !" };
	win.attach(t);
	win.set_label("Canvas n.8");
	win.wait_for_button();
	t.set_font(Font::times_bold);
	t.set_font_size(20);
	win.set_label("Canvas n.9");
	win.wait_for_button();
	Image ii{ Point{ 100,50 },"input_choice.jpg" };
	win.attach(ii);
	win.set_label("Canvas n.10");
	win.wait_for_button();
	ii.move(200,200);
	win.set_label("Canvas n.11");
	win.wait_for_button();
	Circle c{ Point{ 100,200 },50};
	Graph_lib::Ellipse e{ Point{ 100,200 },75,25 };
	e.set_color(Color::dark_red);
	Mark m{ Point{ 100,200 },'x' };
	win.attach(c);
	win.attach(e);
	win.attach(m);
	win.set_label("Canvas n.12");
	win.wait_for_button();
	*/


}




/*
// ***********************************************************************************************************************************
// Test de base livré avec la librairie FLTK : OK !
// Librairies FLTK - Version 1.3.4-2 référencée dans le projet (debug & release)
#include<FL/Fl.h>
#include<FL/Fl_Box.h>
#include<FL/Fl_Window.h>
int main()
{
	// Test de base
	Fl_Window window(400, 400, "Window title");
	Fl_Box box(0, 0, 400, 400, "Hey, I mean, Hello, World !");
	window.show();
	return Fl::run();

}
 */
 // *************************************************************************************************************************************