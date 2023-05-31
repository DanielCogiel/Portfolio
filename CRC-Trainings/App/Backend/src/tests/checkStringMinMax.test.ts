import { checkStringMinMax } from "../utility/validators";

describe('checkStringMinMax',() => {
    it.each([
        ['Adam', 2, 5, true],
        ['', 0, 5, true],
        ['', 10, 20, false],
        ['ntermediate', 10, 255, true],
        ['expert', 20, 50, false],
        ['EXPERT', 10, 20, false],
        [null, 0, 5, true],
        [undefined, 5, 10, false]
    ])('Checks if %p has length between %p and %p expecting %p', (value: string | null | undefined, min: number, max: number, result: boolean) => {
        expect(checkStringMinMax(value, min, max)).toBe(result)
    })
})