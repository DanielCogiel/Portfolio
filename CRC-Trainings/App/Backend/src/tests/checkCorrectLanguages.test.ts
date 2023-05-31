import { checkCorrectLanguage } from "../utility/validators";

describe('checkCorrectLanguage',() => {
    it.each([
        ['eN', true],
        ['', false],
        ['N', false],
        ['PL', true],
        ['pl', true],
        [null, false],
        [undefined, false]
    ])('Checks if %p is correct language expecting %p', (language: string | null | undefined, result: boolean) => {
        expect(checkCorrectLanguage(language)).toBe(result)
    })
})