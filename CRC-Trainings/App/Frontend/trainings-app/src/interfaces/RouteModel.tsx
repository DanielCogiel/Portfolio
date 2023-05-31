import React from 'react';

interface RouteModel {
    path: string,
    component: any,
    HeaderRouteName?: string,
    isCreatorOnly?: boolean,
    hasNotificationNumber?: boolean
}

export default RouteModel;