import type { MouseEventHandler } from "react";

type SquareProps = {
    squareValue: string | null;
    onSquareClick?: MouseEventHandler<HTMLButtonElement>;
};

export default function Square({ squareValue, onSquareClick }: SquareProps) {
    return <button 
        className="square"
        onClick={onSquareClick}
        disabled={squareValue !== null}
    >
        { squareValue }
    </button>;
}