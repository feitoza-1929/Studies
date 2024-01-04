var EventEmitter = require('node:events');

export class BoardService extends EventEmitter
{
    constructor()
    {
        this.cells = [];
        this.players = [];
        this.currentTurn = 0;
        this.ready = false;
        this.events =
        {
            PLAYER_CONNECTED: 'playerConnected',
            GAME_READY: 'gameReady',
            CELL_MARKED: 'cellMarked',
            CHANGE_TURN: 'changeTurn',
            WINNER: 'winner',
            DRAW: 'draw'
        };

        markCell(cellId)
        {
            var cell = cells[cellId];
            if (!cell)
                return false;

            if (this.ready && cell.active)
            {
                var player = this.players[this.currentTurn];
                cell.value = player.label;
                cell.active = false;

                this.emit(BoardService.events.CELL_MARKED, { cellId: cellId, player: player });

                var result = checkWinner();
                if (result.win)
                {
                    this.disableAll();
                    this.emit(BoardService.events.WINNER, { player: this.players[this.currentTurn], position: result.position });
                }
                else if (this.checkDraw())
                {
                    this.emit(BoardService.events.DRAW, {});
                }

            }
            if (this.checkWinner())
            {
                this.emit(BoardService.events.WINNER,{player: this.players[this.currentTurn]});
            }
        }

        checkDraw()
        {
            this.cells.every((cell) => cell.value == this.players[0].label || cell.value == this.players[1].label);
        }

        checkWinner()
        {
        
            var winPositions =
                [
                    [0, 1, 2],
                    [0, 4, 8],
                    [0, 3, 6],
                    [1, 4, 7],
                    [2, 5, 8],
                    [2, 4, 6],
                    [6, 7, 8]
                ];
            
            var player = this.players[this.currentTurn];
            var winnerPosition = [];

            var result = winPositions.some((winPosition) =>
            {
                if (this.cells[winPosition[0]] !== player.label)
                    return false;
                
                var result = this.cells[winPosition[1]] === this.cells[winPosition[0]] && this.cells[winPosition[1]] === cells[winPosition[2]];
                
                if (result)
                {
                    winnerPosition = winPosition;
                    return result;
                }
            });

            return { win: result, winnerPosition: winnerPosition}
        }
    }
}