const Levels = ['BEGINNER', 'INTERMEDIATE', 'EXPERT']
const Languages = ['EN', 'PL']

export function checkEmptyFields(data: Object): boolean {
    if (!Object.values(data).includes('') 
    && !Object.values(data).includes(null) 
    && !Object.values(data).includes(undefined)) return true
    else return false
}

export function checkCorrectLevel(level: string | null | undefined): boolean {
    return Levels.includes(level?.toUpperCase() || '');
}

export function checkCorrectLanguage(language: string | null | undefined): boolean {
    return Languages.includes(language?.toUpperCase() || '')
}

export function checkStringMinMax(value: string | null | undefined, min: number, max: number): boolean {
    return (value?.length || 0) >= min && (value?.length || 0) <= max;
}