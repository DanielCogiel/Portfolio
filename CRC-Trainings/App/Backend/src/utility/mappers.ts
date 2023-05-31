function mapLanguage(lang: string, reverse: boolean = false): string {
    if (!reverse) {
        switch(lang) {
            case 'en': 
                return 'ENGLISH';
            default:
                return 'POLISH';
        }
    } else {
        switch(lang) {
            case 'ENGLISH': 
                return 'en';
            default:
                return 'pl';
        }
    }
}

export default mapLanguage;