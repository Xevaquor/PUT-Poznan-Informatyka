package put.ai.games.qplayer;

import put.ai.games.game.Board;
import put.ai.games.game.Move;
import put.ai.games.game.Player;

import java.util.List;
import java.util.Objects;

/**
 * Created by bednarsm on 2016-01-14.
 */
public class QPlayer extends Player {

    private long startTime;
    private long haveToFinishBefore;

    public static void main(String[] args) {

    }

    private Color myColor, enemyColor;
    private Move bestMove;

    private Object[] minmax(Board board, int depth, boolean isMaximizing){
        if(runningOutOfTime()){
            return new Object[]{ scoreBoard(board)};
        }

        Color nodeColor;
        if(isMaximizing)
            nodeColor = myColor;
        else
            nodeColor = enemyColor;

        List<Move> availableMoves = board.getMovesFor(nodeColor);
        if(depth == 0 || availableMoves.isEmpty())
            return new Object[] {scoreBoard(board), null};
        Color winningColor = board.getWinner(getOpponent(nodeColor));
        if(winningColor == myColor)
            return new Object[] {Integer.MAX_VALUE, null};
        if(winningColor == enemyColor)
            return new Object[] {Integer.MIN_VALUE, null};

        if(isMaximizing) {
            int bestValue = Integer.MIN_VALUE;
            Move bestMove = null;
            for(Move m : availableMoves){
                board.doMove(m);
                Object[] result = minmax(board, depth - 1, !isMaximizing);
                int v_score = (int) result[0];
                board.undoMove(m);
                if(v_score > bestValue)
                {
                    bestValue = v_score;
                    bestMove = m;
                }
            }
            assert bestMove != null;
            return new Object[] {bestValue, bestMove};
        }

        else{
            int bestValue = Integer.MAX_VALUE;
            Move bestMove = null;
            for(Move m : availableMoves){
                board.doMove(m);
                Object[] result = minmax(board, depth - 1, !isMaximizing);
                int v_score = (int) result[0];
                board.undoMove(m);
                if(v_score < bestValue){
                    bestValue = v_score;
                    bestMove = m;
                }
            }
            assert bestMove != null;
            return new Object[] {bestValue, bestMove};

        }
    }

    private boolean noticed = false;

    private boolean runningOutOfTime(){
        boolean alert = System.currentTimeMillis() > haveToFinishBefore;
//        if(alert || !noticed) {
//            System.out.printf("Running out of time! %d\n", System.currentTimeMillis());
//            noticed = true;
//        }
        return alert;
    }

    @Override
    public String getName() {
        return "Mateusz Bednarski 117194 Gordon Freeman 007007";
    }

    @Override
    public Move nextMove(Board board) {
        myColor = getColor();
        enemyColor = getOpponent(myColor);
        startTime = System.currentTimeMillis();
        haveToFinishBefore = startTime + getTime() - 150;



        System.out.println(getTime());
        Object[] results = minmax(board, 3, true);
        System.out.printf("Exited at %d\n", System.currentTimeMillis());
        return (Move) results[1];


//        board.getState()
        /*List<Move> moves = board.getMovesFor(getColor());
        Move bestMove = moves.get(0);
        board.doMove(bestMove);
        int bestScore = scoreBoard(board);
        board.undoMove(bestMove);
        for(Move m : moves){
            int moveScore = scoreAfterMove(board, m);
            if(moveScore > bestScore){
                bestMove = m;
                bestScore = moveScore;
            }
        }
        return bestMove;*/
    }

    private int scoreAfterMove(Board board, Move m){
        board.doMove(m);
        int score = scoreBoard(board);
        board.undoMove(m);
        return score;
    }

    private int scoreBoard(Board board) {
        int boardSize = board.getSize();
        Color myColor = getColor();
        int mineStones = 0;
        int enemyStones = 0;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if(board.getState(i, j) == myColor)
                    mineStones++;
                else if(board.getState(i, j) == getOpponent(myColor))
                    enemyStones++;
            }
        }
        return mineStones - enemyStones;
    }

}
