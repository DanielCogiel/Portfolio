import RouteModel from "../interfaces/RouteModel";
import { Navigate } from "react-router";
import CoursesPage from "../pages/CoursesPage";
import CourseRegistrationPage from "../pages/CourseRegistrationPage";
import LoginPage from "../pages/LoginPage";
import RegistrationPage from "../pages/RegistrationPage";
import NotFoundPage from "../pages/NotFoundPage";
import PersonalCoursesPage from "../pages/PersonalCoursesPage";
import AuthWrapper from "../layouts/AuthWrapper";

const COURSES_URL: string = '/courses'

const routes: RouteModel[] = [
    {
        path: '/',
        component: <Navigate to='/courses/all' />
    },
    {
        path: `${COURSES_URL}/all`,
        component: <AuthWrapper><CoursesPage /></AuthWrapper>,
        HeaderRouteName: 'All courses'
    },
    {
        path: `${COURSES_URL}/personal`,
        component: <AuthWrapper><PersonalCoursesPage /></AuthWrapper>,
        HeaderRouteName: 'My courses',
        hasNotificationNumber: true
    },
    {
        path: `${COURSES_URL}/register`,
        component: <AuthWrapper><CourseRegistrationPage /></AuthWrapper>,
        HeaderRouteName: 'Register new course',
        isCreatorOnly: true
    },
    {
        path: '/login',
        component: <LoginPage />
    },
    {
        path: '/register',
        component: <RegistrationPage />
    },
    {
        path: '*',
        component: <NotFoundPage />
    }
]


export default routes;