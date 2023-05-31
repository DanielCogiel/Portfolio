export const SERVER_URL = process.env.REACT_APP_API_URL
const API_URL = `${SERVER_URL}/api`;
const REGISTER_URL = `${API_URL}/register`;
const LOGIN_URL = `${API_URL}/login`
export const COURSES_API_URL = `${API_URL}/courses`
const REGISTER_COURSE_URL = `${COURSES_API_URL}/register`
const ALL_COURSES_URL = `${COURSES_API_URL}/all`
export const PERSONAL_COURSES_URL = `${COURSES_API_URL}/personal`
const UPLOAD_URL = `${API_URL}/upload`
const IMAGE_STORAGE_URL = `${SERVER_URL}/uploads`

export const API_URLS = {
    COURSES: {
        ALL: ALL_COURSES_URL,
        PERSONAL: PERSONAL_COURSES_URL,
        REGISTER: REGISTER_COURSE_URL
    },
    AUTH: {
        REGISTER: REGISTER_URL,
        LOGIN: LOGIN_URL
    },
    FILES: {
        UPLOAD: UPLOAD_URL,
        STORAGE: IMAGE_STORAGE_URL
    }
}