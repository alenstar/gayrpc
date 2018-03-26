// Generated by github.com/IronsDu/protoc-gen-gayrpc
// Coding by github.com/liuhan907
// DO NOT EDIT!!!

#ifndef _BENCHMARK_SERVICE_H
#define _BENCHMARK_SERVICE_H

#include <string>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include <future>

#include <google/protobuf/util/json_util.h>

#include "meta.pb.h"
#include "benchmark_service.pb.h"

#include "GayRpcCore.h"
#include "GayRpcError.h"
#include "GayRpcTypeHandler.h"
#include "GayRpcClient.h"
#include "GayRpcService.h"
#include "GayRpcReply.h"

namespace dodo {
namespace benchmark {

namespace benchmark_service
{
	using namespace gayrpc::core;
	using namespace google::protobuf::util;
	
	
	enum class EchoServerMsgID:uint64_t
	{
		echo = 2333,
		
	};

	class EchoServerClient : public BaseClient
	{
	public:
		typedef std::shared_ptr<EchoServerClient> PTR;

		typedef std::function<void(const dodo::benchmark::EchoResponse&,
			const gayrpc::core::RpcError&)> EchoHandle;
		

    public:
		void echo(const dodo::benchmark::EchoRequest& request,
			const EchoHandle& handle = nullptr)
		{
			call<dodo::benchmark::EchoResponse>(request, static_cast<uint64_t>(EchoServerMsgID::echo), handle);
		}
		

		 dodo::benchmark::EchoResponse sync_echo(const dodo::benchmark::EchoRequest& request,
			gayrpc::core::RpcError& error)
		{
				auto errorPromise = std::make_shared<std::promise<gayrpc::core::RpcError>>();
            	auto responsePromise = std::make_shared<std::promise<dodo::benchmark::EchoResponse>>();

            	echo(request, [responsePromise, errorPromise](const dodo::benchmark::EchoResponse& response,
                	const gayrpc::core::RpcError& error) {
                	errorPromise->set_value(error);
                	responsePromise->set_value(response);
            	});

            	error = errorPromise->get_future().get();
            	return responsePromise->get_future().get();
		}
		

    public:
        static PTR Create(const RpcTypeHandleManager::PTR& rpcHandlerManager,
            const UnaryServerInterceptor& outboundInterceptor,
            const UnaryServerInterceptor& inboundInterceptor)
        {
            struct make_shared_enabler : public EchoServerClient
            {
            public:
                make_shared_enabler(const UnaryServerInterceptor& outboundInterceptor,
                    const UnaryServerInterceptor& inboundInterceptor)
                    : 
                    EchoServerClient(outboundInterceptor, inboundInterceptor) {}
            };

            auto client = PTR(new make_shared_enabler(outboundInterceptor, inboundInterceptor));
            client->installResponseStub(rpcHandlerManager);

            return client;
        }

    private:
        using BaseClient::BaseClient;
    };

	typedef TemplateReply<dodo::benchmark::EchoResponse> EchoReply;
	

    class EchoServerService : public BaseService
    {
    public:
        typedef std::shared_ptr<EchoServerService> PTR;
        virtual ~EchoServerService()
        {
        }

        virtual void onClose() {}

    private:
		virtual bool echo(const dodo::benchmark::EchoRequest& request, 
            const EchoReply::PTR& replyObj) = 0;
		

    private:
        friend  void registerEchoServerService(gayrpc::core::RpcTypeHandleManager::PTR rpcTypeHandleManager,
            const EchoServerService::PTR& service,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor);

		static bool echo_stub(const RpcMeta& meta,
			const std::string& data,
			const EchoServerService::PTR& service,
			const UnaryServerInterceptor& inboundInterceptor,
			const UnaryServerInterceptor& outboundInterceptor)
		{
			dodo::benchmark::EchoRequest request;
			if (!request.ParseFromString(data))
			{
			    std::cerr << "parse EchoRequst error " << std::endl;
			    return false;
			}

			inboundInterceptor(meta,
			    request,
			    [service,
			    outboundInterceptor,
			    &request](const RpcMeta& meta, const google::protobuf::Message& message) {
			    auto replyObject = std::make_shared<EchoReply>(meta, outboundInterceptor);
			    service->echo(request, replyObject);
			});
			return true;
		}
		
    };

	inline void registerEchoServerService(gayrpc::core::RpcTypeHandleManager::PTR rpcTypeHandleManager,
        const EchoServerService::PTR& service,
        const UnaryServerInterceptor& inboundInterceptor,
        const UnaryServerInterceptor& outboundInterceptor)
    {
		typedef std::function<bool(const RpcMeta&,
		    const std::string& data,
		    const EchoServerService::PTR&,
		    const UnaryServerInterceptor&,
		    const UnaryServerInterceptor&)> EchoServerServiceRequestHandler;

		typedef std::unordered_map<uint64_t, EchoServerServiceRequestHandler> EchoServerServiceHandlerMap;

		auto serviceHandlerMap = std::make_shared<EchoServerServiceHandlerMap>();

		(*serviceHandlerMap)[static_cast<uint64_t>(EchoServerMsgID::echo)] = EchoServerService::echo_stub;
		

		auto requestStub = [service,
		    serviceHandlerMap,
		    inboundInterceptor,
		    outboundInterceptor](const RpcMeta& meta, const std::string& data) {
		    if (meta.type() == RpcMeta::REQUEST)
		    {
		        auto it = serviceHandlerMap->find(meta.request_info().method());
		        if (it == serviceHandlerMap->end())
		        {
		            std::cerr << "not found handle, method:" << meta.request_info().method();
		            return false;
		        }

		        (*it).second(meta,
		            data,
		            service,
		            inboundInterceptor,
		            outboundInterceptor);
		    }
		    return true;
		};
		rpcTypeHandleManager->registerTypeHandle(RpcMeta::REQUEST, requestStub);
	}
	
}

}
}

#endif

