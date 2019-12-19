// Generated by github.com/IronsDu/protoc-gen-gayrpc
// Coding by github.com/liuhan907
// DO NOT EDIT!!!

#ifndef DODO_BENCHMARK_BENCHMARK_SERVICE_H
#define DODO_BENCHMARK_BENCHMARK_SERVICE_H

#include <string_view>
#include <string>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include <future>
#include <chrono>

#include <google/protobuf/util/json_util.h>

#include <gayrpc/core/gayrpc_meta.pb.h>
#include "benchmark_service.pb.h"

#include <gayrpc/core/GayRpcType.h>
#include <gayrpc/core/GayRpcError.h>
#include <gayrpc/core/GayRpcTypeHandler.h>
#include <gayrpc/core/GayRpcClient.h>
#include <gayrpc/core/GayRpcService.h>
#include <gayrpc/core/GayRpcReply.h>
#include <ananas/future/Future.h>

namespace dodo {
namespace benchmark {

    using namespace gayrpc::core;
    using namespace google::protobuf::util;
    
    enum class benchmark_service_ServiceID:uint32_t
    {
        EchoServer,
        
    };

    
    enum class EchoServerMsgID:uint64_t
    {
        Echo = 2333,
        
    };

    class EchoServerClient : public BaseClient
    {
    public:
        using PTR = std::shared_ptr<EchoServerClient>;
        using WeakPtr = std::weak_ptr<EchoServerClient>;

        using EchoHandle = std::function<void(const dodo::benchmark::EchoResponse&, std::optional<gayrpc::core::RpcError>)>;
        

    public:
        void Echo(const dodo::benchmark::EchoRequest& request,
            const EchoHandle& handle = nullptr)
        {
            call<dodo::benchmark::EchoResponse>(request, 
                static_cast<uint32_t>(benchmark_service_ServiceID::EchoServer), 
                static_cast<uint64_t>(EchoServerMsgID::Echo), 
                handle);
        }
        
        void Echo(const dodo::benchmark::EchoRequest& request,
            const EchoHandle& handle,
            std::chrono::seconds timeout, 
            BaseClient::TIMEOUT_CALLBACK&& timeoutCallback)
        {
            call<dodo::benchmark::EchoResponse>(request, 
                static_cast<uint32_t>(benchmark_service_ServiceID::EchoServer), 
                static_cast<uint64_t>(EchoServerMsgID::Echo), 
                handle,
                timeout,
                std::move(timeoutCallback));
        }

        
        ananas::Future<std::pair<dodo::benchmark::EchoResponse, std::optional<gayrpc::core::RpcError>>> SyncEcho(
            const dodo::benchmark::EchoRequest& request,
            std::chrono::seconds timeout)
        {
            ananas::Promise<std::pair<dodo::benchmark::EchoResponse, std::optional<gayrpc::core::RpcError>>> promise;

            Echo(request, 
                [promise](const dodo::benchmark::EchoResponse& response,
                    std::optional<gayrpc::core::RpcError> error) mutable {
                    promise.SetValue(std::make_pair(response, error));
                },
                timeout,
                [promise]() mutable {
                    dodo::benchmark::EchoResponse response;
                    gayrpc::core::RpcError error;
                    error.setTimeout();
                    promise.SetValue(std::make_pair(response, std::optional<gayrpc::core::RpcError>(error)));
                });

            return promise.GetFuture();
        }

        

    public:
        static PTR Create(const RpcTypeHandleManager::PTR& rpcHandlerManager,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor)
        {
            class make_shared_enabler : public EchoServerClient
            {
            public:
                make_shared_enabler(const RpcTypeHandleManager::PTR& rpcHandlerManager,
                    const UnaryServerInterceptor& inboundInterceptor,
                    const UnaryServerInterceptor& outboundInterceptor)
                    : 
                    EchoServerClient(rpcHandlerManager, inboundInterceptor, outboundInterceptor) {}
            };

            auto client = PTR(new make_shared_enabler(rpcHandlerManager, inboundInterceptor, outboundInterceptor));
            client->installResponseStub(rpcHandlerManager, static_cast<uint32_t>(benchmark_service_ServiceID::EchoServer));

            return client;
        }

        static  std::string GetServiceTypeName()
        {
            return "dodo::benchmark::EchoServer";
        }

    private:
        using BaseClient::BaseClient;
    };

    class EchoServerService : public BaseService
    {
    public:
        using PTR = std::shared_ptr<EchoServerService>;
        using WeakPtr = std::weak_ptr<EchoServerService>;

        using EchoReply = TemplateReply<dodo::benchmark::EchoResponse>;
        

        using BaseService::BaseService;

        virtual ~EchoServerService()
        {
        }

        virtual void onClose() {}

        static bool Install(const EchoServerService::PTR& service);

        static  std::string GetServiceTypeName()
        {
            return "dodo::benchmark::EchoServer";
        }
    private:
        virtual void Echo(const dodo::benchmark::EchoRequest& request, 
            const dodo::benchmark::EchoServerService::EchoReply::PTR& replyObj,
            InterceptorContextType&&) = 0;
        

    private:

        static auto Echo_stub(RpcMeta&& meta,
            const std::string_view& data,
            const EchoServerService::PTR& service,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor,
            InterceptorContextType&& context)
        {
            dodo::benchmark::EchoRequest request;
            return parseRequestWrapper(request, std::move(meta), data, inboundInterceptor, [service,
                outboundInterceptor = outboundInterceptor,
                &request](RpcMeta&& meta, const google::protobuf::Message& message, InterceptorContextType&& context) mutable {
                auto replyObject = std::make_shared<EchoReply>(std::move(meta), std::move(outboundInterceptor));
                service->Echo(request, replyObject, std::move(context));
                return ananas::MakeReadyFuture(std::optional<std::string>(std::nullopt));
            }, std::move(context));
        }

        
    };

    inline bool EchoServerService::Install(const EchoServerService::PTR& service)
    {
        auto rpcTypeHandleManager = service->getServiceContext().getTypeHandleManager();
        auto inboundInterceptor = service->getServiceContext().getInInterceptor();
        auto outboundInterceptor = service->getServiceContext().getOutInterceptor();

        using EchoServerServiceRequestHandler = std::function<InterceptorReturnType(RpcMeta&&,
            const std::string_view& data,
            const EchoServerService::PTR&,
            const UnaryServerInterceptor&,
            const UnaryServerInterceptor&,
            InterceptorContextType&& context)>;

        using EchoServerServiceHandlerMapById = std::unordered_map<uint64_t, EchoServerServiceRequestHandler>;
        using EchoServerServiceHandlerMapByStr = std::unordered_map<std::string, EchoServerServiceRequestHandler>;

        EchoServerServiceHandlerMapById serviceHandlerMapById = {
            {static_cast<uint64_t>(EchoServerMsgID::Echo), EchoServerService::Echo_stub},
            
        };
        EchoServerServiceHandlerMapByStr serviceHandlerMapByStr = {
            {"dodo.benchmark.EchoServer.Echo", EchoServerService::Echo_stub},
            
        };

        auto requestStub = [service,
            serviceHandlerMapById,
            serviceHandlerMapByStr,
            inboundInterceptor,
            outboundInterceptor](RpcMeta&& meta, const std::string_view& data, InterceptorContextType&& context) {
            
            if (meta.type() != RpcMeta::REQUEST)
            {
                throw std::runtime_error("meta type not request, It is:" + std::to_string(meta.type()));
            }
            
            EchoServerServiceRequestHandler handler;
            try
            {
                if (!meta.request_info().strmethod().empty())
                {
                    auto it = serviceHandlerMapByStr.find(meta.request_info().strmethod());
                    if (it == serviceHandlerMapByStr.end())
                    {
                        throw std::runtime_error("not found handle, method:" + meta.request_info().strmethod());
                    }
                    handler = (*it).second;
                }
                else
                {
                    auto it = serviceHandlerMapById.find(meta.request_info().intmethod());
                    if (it == serviceHandlerMapById.end())
                    {
                        throw std::runtime_error("not found handle, method:" + meta.request_info().intmethod());
                    }
                    handler = (*it).second;
                }
            }
            catch (const std::exception& e)
            {
                auto tmpMeta = meta;
                auto tmpOutboundInterceptor = outboundInterceptor;
                BaseReply reply(std::move(tmpMeta), std::move(tmpOutboundInterceptor));
                reply.error<RpcMeta>(0, e.what(), InterceptorContextType());

                return;
            }

            handler(std::move(meta),
                data,
                service,
                inboundInterceptor,
                outboundInterceptor,
                std::move(context))
                .Then([=](std::optional<std::string> err) {
                        if (err)
                        {
                            auto tmpMeta = meta;
                            auto tmpOutboundInterceptor = outboundInterceptor;
                            BaseReply reply(std::move(tmpMeta), std::move(tmpOutboundInterceptor));
                            // TODO::错误码0可能和业务层的错误码冲突!
                            reply.error<RpcMeta>(0, err.value(), InterceptorContextType());
                        }
                    });
        };

        return rpcTypeHandleManager->registerTypeHandle(RpcMeta::REQUEST, requestStub, static_cast<uint32_t>(benchmark_service_ServiceID::EchoServer));
    }
    
}
}

#endif

