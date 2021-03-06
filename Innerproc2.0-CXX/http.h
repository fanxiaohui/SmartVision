//
// Created by bin zhang on 2019/1/6.
//

#ifndef INNERPROC_HTTP_H
#define INNERPROC_HTTP_H

#include <thread>
#include <atomic>
#include "base.h"
#include "service.h"
#include "mongoose.h"

struct HttpRequest{
	std::string url;
	PropertyMap head;
	std::string method;
	std::string content;
};

struct HttpResponse{

};

typedef std::map< std::string, std::string> HttpHeaders_t;

class HttpService:Service{

public:
	static std::shared_ptr<HttpService>& instance(){
		static std::shared_ptr<HttpService> handle ;
		if(!handle.get()){
			handle = std::make_shared<HttpService>() ;
		}
		return handle;
	}
	
	bool  init(const Config& cfgs);
	
	bool open();
	void close();
	void run();
public:
	static void ev_handler(struct mg_connection *nc, int ev, void *ev_data);
	void handle_innerdevice_register(struct mg_connection *nc, struct http_message *hm );
	void handle_innerdevice_remove(struct mg_connection *nc, struct http_message *hm );
	void handle_innerdevice_discover(struct mg_connection *nc, struct http_message *hm );
	void handle_status_query(struct mg_connection *nc, struct http_message *hm );
	void handle_innerdevice_list(struct mg_connection *nc, struct http_message *hm );
	
	void handle_innerdevice_login(struct mg_connection *nc, struct http_message *hm );
	void handle_seczone_passwd_set(struct mg_connection *nc, struct http_message *hm );
	
	bool check_auth(struct http_message *hm ,const std::string& code="token" );
	
	void thread_run();

private:
	Config 	cfgs_;
//	std::shared_ptr<std::thread> thread_;
	std::atomic_bool running_;
	
};

//class InnerServiceHandler:HttpHandler{
//
//	void onRequest(const std::shared_ptr<HttpRequest>& req,std::shared_ptr<HttpResponse>& resp);
//
//};



#endif //INNERPROC_HTTP_H
