import Square from './Square.tsx';

type BoardProps = {
  xIsNext: boolean;
  squares: (string | null)[];
  onPlay: (nextSquares: (string | null)[]) => void;
};

export default function Board({ xIsNext, squares, onPlay }: BoardProps) {
  function calculateWinner(squares: (string | null)[]) {
    const lines = [
      [0, 1, 2],
      [3, 4, 5],
      [6, 7, 8],
      [0, 3, 6],
      [1, 4, 7],
      [2, 5, 8],
      [0, 4, 8],
      [2, 4, 6],
    ];

    for (let i = 0; i < lines.length; i++) {
      const [a, b, c] = lines[i];
      if (squares[a] && squares[a] === squares[b] && squares[a] === squares[c]) {
        return squares[a];
      }
    }

    return null;
  }

  function handleClick(i: number) {
    if (calculateWinner(squares) || squares[i]) {
      return;
    }

    const nextSquares = squares.slice();
    nextSquares[i] = xIsNext ? 'X' : 'O';
    
    onPlay(nextSquares);
  }

  const winner = calculateWinner(squares);
  let status;

  if (winner) {
    status = 'Winner: ' + winner;
  } else {
    status = 'Next player: ' + (xIsNext ? 'X' : 'O');
  }

  return (
    <>
      <div className="status">{status}</div>
      <div className="board-row">
        <Square squareValue={squares[0]} onSquareClick={() => handleClick(0)} />
        <Square squareValue={squares[1]} onSquareClick={() => handleClick(1)} />
        <Square squareValue={squares[2]} onSquareClick={() => handleClick(2)} />
      </div>
      <div className="board-row">
        <Square squareValue={squares[3]} onSquareClick={() => handleClick(3)} />
        <Square squareValue={squares[4]} onSquareClick={() => handleClick(4)} />
        <Square squareValue={squares[5]} onSquareClick={() => handleClick(5)} />
      </div>
      <div className="board-row">
        <Square squareValue={squares[6]} onSquareClick={() => handleClick(6)} />
        <Square squareValue={squares[7]} onSquareClick={() => handleClick(7)} />
        <Square squareValue={squares[8]} onSquareClick={() => handleClick(8)} />
      </div>
    </>
  );
}