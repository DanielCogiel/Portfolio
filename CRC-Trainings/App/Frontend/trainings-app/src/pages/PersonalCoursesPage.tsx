import CoursesPage from './CoursesPage';
import { API_URLS } from '../config/api';
 
class PersonalCoursesPage extends CoursesPage {
    ENDPOINT: string = API_URLS.COURSES.PERSONAL;
}
 
export default PersonalCoursesPage;