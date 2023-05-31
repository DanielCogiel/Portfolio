interface UserModel {
    username: string, 
    password: string,
    confirmedPassword?: string,
    name: string,
    surname: string, 
    email: string, 
    isCreator: boolean
}

export default UserModel;