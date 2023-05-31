import { checkCorrectLevel } from "../utility/validators";

describe('checkCorrectLevel',() => {
    it.each([
        ['BeGinnEr', true],
        ['', false],
        ['ntermediate', false],
        ['expert', true],
        ['EXPERT', true],
        [null, false],
        [undefined, false]
    ])('Checks if %p is correct level expecting %p', (level: string | null | undefined, result: boolean) => {
        expect(checkCorrectLevel(level)).toBe(result)
    })
})