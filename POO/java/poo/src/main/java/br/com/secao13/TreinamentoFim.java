
package br.com.secao13;

/**
 *
 * @author silas
 */
public class TreinamentoFim extends Treinamento{

    @Override
    public void preparoFisico() {
        System.out.println("preparo fisico de fim de temporada"); 
    }

    @Override
    public void jogoTreino() {
        System.out.println("jogo treino de fim de temporada"); 
    }
    
}
