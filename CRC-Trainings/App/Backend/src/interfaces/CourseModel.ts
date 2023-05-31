interface CourseModel {
    id: number,
    owner_id?: number,
    owner?: string,
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