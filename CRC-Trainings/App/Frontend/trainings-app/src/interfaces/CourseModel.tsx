import { Level, Language } from "../config/enums"

interface CourseModel {
    username?: string | null,
    id?: number,
    title: string,
    language: string,
    date: {
        start: string,
        finish: string
    },
    hours: {
        start: string,
        finish: string,
        times: number
    },
    level: string,
    location: string,
    trainer: string,
    isEnrolled?: boolean,
    isOwner?: boolean,
    image?: any
}

export default CourseModel;