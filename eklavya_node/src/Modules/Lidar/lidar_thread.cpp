/*
 * Lidar Processing Node
 * Subscribes to scan published by hokuyo_node
 * 
 * */

#include "LidarData.h"

//#define FPS_TEST

char **laser_scan;

void *lidar_thread(void *arg) {
    ros::NodeHandle lidar_node;

    ros::Subscriber sub = lidar_node.subscribe("scan", 5, LidarData::update_map);
    ros::Rate loop_rate(LOOP_RATE);

    ROS_INFO("Lidar thread started");

#ifdef FPS_TEST
    cout << "[LIDAR] Conducting an FPS Test" << endl;
    int iterations = 0;
    time_t start = time(0);
#endif

    while (ros::ok()) {
#ifdef FPS_TEST
        if (iterations > 100) {
            time_t finish = time(0);
            double fps = (iterations + 0.0) / (finish - start);
            cout << "[LIDAR] FPS: " << fps << endl;
            break;
        }

        iterations++;
#endif

        ros::spinOnce();
        loop_rate.sleep();
    }

    return NULL;
}

