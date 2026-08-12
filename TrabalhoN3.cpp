/* Trabalho labirinto
Aluno: Leonardo Pimentel Rodrigues da Rosa */

#include <stdio.h>
#include <stdlib.h>


#define LINHAS 21
#define COLUNAS 51


char lab[LINHAS][COLUNAS + 1] = {
	"###################################################",
	"#E..#.....#.......#.....#.........#.....#.........#",
	"#.#.#.###.#.#####.#.###.#.#######.#.###.#.#######.#",
	"#.#...#...#.....#.#...#.#.#.....#...#...#.#.......#",
	"#.#####.#######.#.###.#.#.#.###.#####.###.#.#####.#",
	"#.......#.......#.....#...#...#.......#...#.......#",
	"#######.#.#############.#####.#######.#.###########",
	"#.......#...#.....#.....#.....#.......#.....#.....#",
	"#.#########.#.###.#.#####.###.#.#########.#.#.###.#",
	"#.#.........#...#.#.#.....#...#.#.....#...#.#...#.#",
	"#.#.#############.#.#.#####.###.#.###.#.###.###.#.#",
	"#.#.#.............#.#.#.....#...#...#.#...#.....#.#",
	"#.#.#.###########.#.#.#.#####.#####.#.###.#######.#",
	"#.#.#.#...........#.#.#.#.....#.....#.....#.......#",
	"#.#.#.#.###########.#.#.#.#####.###########.#####.#",
	"#.#...#.............#.#.#.......#...........#.....#",
	"#.#################.#.#.#########.#########.#.###.#",
	"#...................#.#...........#.........#.#...#",
	"#.###################.###########.#########.#.###.#",
	"#.....................#...........#.........#....S#",
	"###################################################"
};


int veio_de[LINHAS][COLUNAS];


int fila[LINHAS * COLUNAS];
int inicio = 0, fim = 0;


int dl[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};


void mostrar(void) {
	int i;

	for (i = 0; i < LINHAS; i++) {
		printf("%s\n", lab[i]);
	}
}


void localizar(int *el, int *ec, int *LinhaSaida, int *ColunaSaida) {
	int i, j;

	*el = -1;
	*ec = -1;
	*LinhaSaida = -1;
	*ColunaSaida = -1;

	for (i = 0; i < LINHAS; i++) {
		for (j = 0; j < COLUNAS; j++) {
			if (lab[i][j] == 'E') {
				*el = i;
				*ec = j;
			}

			if (lab[i][j] == 'S') {
				*LinhaSaida = i;
				*ColunaSaida = j;
			}
		}
	}
}


void buscar(int el, int ec, int LinhaSaida, int ColunaSaida) {
	int atual, LinhaAtual, ColunaAtual, nl, nc, d;

	fila[fim++] = el * COLUNAS + ec;
	veio_de[el][ec] = -1;

	while (inicio < fim) {
		atual = fila[inicio++];
		LinhaAtual = atual / COLUNAS;
		ColunaAtual = atual % COLUNAS;

		if (LinhaAtual == LinhaSaida && ColunaAtual == ColunaSaida) {
			break;
		}

		for (d = 0; d < 4; d++) {
			nl = LinhaAtual + dl[d];
			nc = ColunaAtual + dc[d];

			if (nl >= 0 && nl < LINHAS && nc >= 0 && nc < COLUNAS && lab[nl][nc] != '#' && !veio_de[nl][nc]) {
				veio_de[nl][nc] = d + 1;
				fila[fim++] = nl * COLUNAS + nc;
			}
		}
	}
}

int marcarCaminho(int el, int ec, int LinhaSaida, int ColunaSaida) {
	int LinhaAtual, ColunaAtual, d, passos = 0;

	LinhaAtual = LinhaSaida;
	ColunaAtual = ColunaSaida;

	while (LinhaAtual != el || ColunaAtual != ec) {
		d = veio_de[LinhaAtual][ColunaAtual] - 1;
		LinhaAtual -= dl[d];
		ColunaAtual -= dc[d];

		if (lab[LinhaAtual][ColunaAtual] != 'E') {
			lab[LinhaAtual][ColunaAtual] = '*';
		}

		passos++;
	}

	return passos;
}

int main(void) {
	int el, ec, LinhaSaida, ColunaSaida, passos;

	localizar(&el, &ec, &LinhaSaida, &ColunaSaida);

	if (el == -1 || ec == -1 || LinhaSaida == -1 || ColunaSaida == -1) {
		printf("Entrada ou saida nao encontrada.\n");
		return 0;
	}

	printf("Labirinto original\n\n");
	mostrar();

	buscar(el, ec, LinhaSaida, ColunaSaida);

	if (!veio_de[LinhaSaida][ColunaSaida]) {
		printf("\nNao existe caminho entre a entrada e a saida.\n");
		return 0;
	}

	passos = marcarCaminho(el, ec, LinhaSaida, ColunaSaida);

	printf("\nLabirinto resolvido\n\n");
	mostrar();
	printf("\nCaminho encontrado em %d passos.\n", passos);

	return 0;
}
