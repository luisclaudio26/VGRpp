#include "../../inc/element/triangle.h"
#include "../../inc/vector/numeric.h"

#include <iostream>

// Lembre-se que podemos desenhar o triângulo com os pontos
// "existindo" no espaço da tela, i.e. aplicando xf e depois scene_xf
// aos vértices e depois desenhando.

//---------------------------------------
//-------------- INTERNAL ---------------
//---------------------------------------
void compute_implicit_line(const Vec2& p0, const Vec2& p1, double* coef)
{
	// Aqui você calcula a, b e c para a equação de forma
	// ax+by+c = 0 que passa por p0 e p1.

	//Vetor que vai de p0 até p1
	Vec2 v = p1 - p0;

	//Vetor ortogonal a v
	Vec2 v_ort( -v.y(), v.x() );

	double a = v_ort.x();
	double b = v_ort.y();
	double c = -v_ort.dot(p0);

	coef[0] = a;
	coef[1] = b;
	coef[2] = c;
}

//----------------------------------------------
//-------------- FROM TRIANGLE.h ---------------
//----------------------------------------------
Triangle::Triangle(const Vec2& p0, const Vec2& p1, const Vec2& p2)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;

	//Compute implicit equation for each edge
	implicitize();
}

bool Triangle::is_inside(double x, double y)
{
	// Aqui você retorna VERDADEIRO ou FALSO se o ponto
	// (x,y) está dentro ou fora do triângulo. Para isso,
	// verifique se (x,y) está DO MESMO LADO* de todas as
	// retas.
	//
	// * "Do mesmo lado" significa que, orientando as retas
	// (definindo onde o segmento reta "começa" e "termina")
	// em sentido horário/anti-horário, o ponto vai estar à
	// à direita ou à esquerda de todas as retas ao mesmo tempo.

	double line1 = edge[0]*x + edge[1]*y + edge[2];
	double line2 = edge[3]*x + edge[4]*y + edge[5];
	double line3 = edge[6]*x + edge[7]*y + edge[8];

	return Numeric::sign(line1) == Numeric::sign(line2) &&
			Numeric::sign(line2) == Numeric::sign(line3);
}

void Triangle::set_modelxf(const Matrix3& model_xf)
{
	//Cada vez que a gente muda a transformação do MODELO, temos que
	//recalcular onde os pontos estarão na tela.
	this->model_xf = model_xf;
	implicitize();
}

void Triangle::set_scenexf(const Matrix3& scene_xf)
{
	//Cada vez que a gente muda a transformação da CENA, temos
	//que recalcular onde os pontos estarão na tela.
	this->scene_xf = scene_xf;
	implicitize();
}

void Triangle::implicitize()
{
	// Para o primeiro laboratório, ignore o texto abaixo e pule direto
	// para a função compute_implicit_line().
	//
	// ---------------------------------------------------------------
	//
	// Aqui você deve aplicar a transformação do modelo
	// aos vértices, depois a transformação da cena
	//
	// Não esqueça que as transformações são matrizes 3x3
	// e portanto devem ser aplicados a pontos HOMOGÊNEOS,
	// que depois são "convertidos" de volta para pontos euclidianos.
	//
	// Lembre-se de não transformar os pontos p0, p1, p2 diretamente,
	// pois se mudamos a transformação scene_xf ou model_xf precisaremos
	// "lembrar" onde os pontos estavam originalmente (isto é, precisamos
	// saber as coordenadas dos pontos tal como foram definidos no arquivo .2d)
	
	Matrix3 T = scene_xf * model_xf;

	Vec2 p0_t = T.apply( p0.homogeneous() ).euclidean();
	Vec2 p1_t = T.apply( p1.homogeneous() ).euclidean();
	Vec2 p2_t = T.apply( p2.homogeneous() ).euclidean();

	// Uma vez que os pontos foram transformados, podemos
	// calcular a equação implícita para cada uma das arestas.
	// No cabeçalho triangle.h nós definimos um vetor double edge[9],
	// que deverá armazenar os três parâmetros (a, b, c, de ax + by + c = 0)
	// de cada uma das três arestas.

	compute_implicit_line(p0_t, p1_t, edge);
	compute_implicit_line(p1_t, p2_t, &edge[3]);
	compute_implicit_line(p2_t, p0_t, &edge[6]);
}