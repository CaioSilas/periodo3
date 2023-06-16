
package br.com.secao13;

/**
 *
 * @author silas
 */
public class TreinamentoInicio extends Treinamento {

    @Override
    public void preparoFisico() {
       System.out.println("preparo fisico de inicio de temporada");
    }

    @Override
    public void jogoTreino() {
        System.out.println("jogo treino de inicio de temporada"); 
    }
    
}
