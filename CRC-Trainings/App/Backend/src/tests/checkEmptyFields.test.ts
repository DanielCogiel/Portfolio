import { checkEmptyFields } from "../utility/validators";

describe('CheckEmptyFields', () => {
    it.each([
        [{}, true],
        [{username: 'Daniel', surname: ''}, false],
        [{username: 'Daniel', surname: null}, false],
        [{username: 'Daniel', surname: 'Nowak'}, true],
        [{username: undefined, surname: 'Nowak'}, false]
    ])('Checks if %p does not have empty fields expecting %p', (data: Object, result: boolean) => {
        expect(checkEmptyFields(data)).toBe(result);
    })
})

