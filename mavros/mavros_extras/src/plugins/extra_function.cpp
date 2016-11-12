#include <functional>
#include <mavros/utils.h>
#include <mavros/mavros_plugin.h>
#include <mavros_msgs/ExtraFunction.h>
#include "std_msgs/Float32.h"


namespace mavros {
namespace extra_plugins{


class ExtraFunctionPlugin : public plugin::PluginBase {
public:
	ExtraFunctionPlugin() : PluginBase(),
		extra_function_nh("~extra_function"),
		tf_rate(2.0)
	{ }

	void initialize(UAS &uas_)
	{
		PluginBase::initialize(uas_);
		bool tf_listen;

		extra_function_nh.param<std::string>("frame_id", frame_id, "extra_function");

		extra_function_nh.param("tf/listen", tf_listen, false);
		extra_function_nh.param<std::string>("tf/frame_id", tf_frame_id, "extra_function");
		extra_function_nh.param("tf/rate_limit", tf_rate, 50.0);

		if (tf_listen) {
			ROS_INFO_STREAM_NAMED("extra", "Listen to extra parameters transform "
					<< tf_frame_id);
		}
		else {
			extra_function_sub = extra_function_nh.subscribe("/extra_function",10,&ExtraFunctionPlugin::extra_function_send_cb,this);
		}

		
	}

	Subscriptions get_subscriptions()
	{
		return { /* Rx disabled */ };
	}

private:
	ros::NodeHandle extra_function_nh;

	std::string frame_id;
	ros::Subscriber extra_function_sub;
	std::string tf_frame_id;

	double tf_rate;


	/* -*- mid-level helpers -*- */

	/**
	 * @brief Send setpoint to FCU position controller.
	 *
	 * @warning Send only XYZ, Yaw. ENU frame.
	 */
	void extra_function_send(unsigned short obs_avoid_enable, unsigned short laser_height_enable, unsigned short add_one, unsigned short add_two, unsigned short add_three) {
		mavros::UAS *m_uas_;// = static_cast<D *>(this)->m_uas;
		mavlink::common::msg::EXTRA_FUNCTION sp;

		m_uas_->msg_set_target(sp);
		
		sp.obs_avoid_enable = obs_avoid_enable; /*< bool for obstacle avoidance*/
		sp.laser_height_enable = laser_height_enable; /*< bool for control height by laser*/
		sp.add_one = add_one; /*< additional function bool 1*/
		sp.add_two = add_two; /*< additional function bool 2*/
		sp.add_three = add_three; /*< additional function bool 3*/

		UAS_FCU(m_uas_)->send_message_ignore_drop(sp);		
	}

	/* -*- callbacks -*- */

	 void extra_function_send_cb(const mavros_msgs::ExtraFunction &msg){
        extra_function_send(msg.obs_avoid_enable, msg.laser_height_enable, msg.add_one, msg.add_two, msg.add_three);
	}
};
}	// namespace std_plugins
}	// namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::extra_plugins::ExtraFunctionPlugin, mavros::plugin::PluginBase)
