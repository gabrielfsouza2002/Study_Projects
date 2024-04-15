import java.text.DecimalFormat;
import java.util.Random;

public class FDP {

	public static void main(String[] args) {

		Random random = new Random();

		double [] valor = new double [100];
		DecimalFormat df = new DecimalFormat("###.##");

		System.out.print("A lista com 100 valores de Y de acordo com a FDP dada pode ser: " + "[");

		for(int j = 0; j<100; j++) {

			int numero = random.nextInt(100);

			if(numero <= 9) {
				valor[j] = -1.7;
				}
			else if(numero <= 29) {
				valor[j] = 2.3;
				}
			else if(numero <= 84) {
				valor[j] = 3.8;
				}
			else if(numero <= 100) {
				valor[j] = 5.4;
				}
			System.out.print( valor[j] + ", " );
			}

		System.out.print("]");

		int soma1 = 0;
		int soma2 = 0;
		int soma3 = 0;
		int soma4 = 0;

		for (double c : valor) {
			if (c == -1.7) {
				soma1 = soma1 + 1;
			}

			if (c == 2.3) {
				soma2 = soma2 + 1;
			}

			if (c == 3.8) {
				soma3 = soma3 + 1;
			}

			if (c == 5.4) {
				soma4 = soma4 + 1;
			}
		}


		System.out.println();
		System.out.println();
		System.out.println("==================== Frequencia Absoluta ===================");
		System.out.println();

		System.out.println("A quantidade de vezes que y assumiu valor -1.7, foi: " + soma1);
		System.out.println("A quantidade de vezes que y assumiu valor 2.3, foi: " + soma2);
		System.out.println("A quantidade de vezes que y assumiu valor 3.8, foi: " + soma3);
		System.out.println("A quantidade de vezes que y assumiu valor 5.4, foi: " + soma4);

		double total = 100;

		double FR1 = soma1/total;
		double FR2 = soma2/total;
		double FR3 = soma3/total;
		double FR4 = soma4/total;

		String AC1 = df.format(FR1);
		String AC2 = df.format(FR1 + FR2);
		String AC3 = df.format(FR1 + FR2 + FR3);
		String AC4 = df.format(FR1 + FR2 + FR3 + FR4);


		System.out.println();
		System.out.println("==================== Tabela de Frequencia ===================");
		System.out.println();
		System.out.println("==========================================================");
		System.out.println("| Valor (y) |" + " Frequencia Relativa |" + " Frequencia Acumulada |" + "\n" + "|   -1.7    |" + "        " + FR1 + "         | " + "       " + AC1 + "          |" + "\n" + "|    " + "2.3" + "    |" + "        " + FR2 + "         |" + "        " + AC2 + "          |" + "\n" + "|    " + "3.8" + "    |" + "        " + FR3 + "         |" + "        " + AC3 + "          |" + "\n" + "| " + "   5.4" + "    |" + "        " + FR4 + "         |" + "         " + AC4 + "            |" + "\n" +"| " + "  Total" + "   |" + "        1.0" + "          |" + "        1.0" + "           |"  );
		System.out.println("==========================================================");


		}
	}

