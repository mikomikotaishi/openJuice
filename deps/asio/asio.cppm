/**
 * @file asio.cppm
 * @module asio
 * @brief File containing the module declaration for asio
 * This module re-exports tomlplusplus to asio for convenience, and 
 * re-aliases all tomlplusplus types to PascalCase.
 */

module;

#include <asio.hpp>

export module asio;

export namespace asio {
    constexpr auto PREFER = asio::prefer;
    constexpr auto QUERY = asio::query;
    constexpr auto REQUIRE = asio::require;
    constexpr auto REQUIRE_CONCEPT = asio::require_concept;

    template <typename T, typename Prop>
    using CanPrefer = asio::can_prefer<T, Prop>;

    template <typename T, typename Prop>
    using CanQuery = asio::can_query<T, Prop>;

    template <typename T, typename Prop>
    using CanRequire = asio::can_require<T, Prop>;

    template <typename T, typename Prop>
    using CanRequireConcept = asio::can_require_concept<T, Prop>;

    template <typename T, typename... Props>
    using IsNothrowPrefer = asio::is_nothrow_prefer<T, Props...>;

    template <typename T, typename Prop>
    using IsNothrowQuery = asio::is_nothrow_query<T, Prop>;

    template <typename T, typename... Props>
    using IsNothrowRequire = asio::is_nothrow_require<T, Props...>;

    template <typename T, typename Prop>
    using IsNothrowRequireConcept = asio::is_nothrow_require_concept<T, Prop>;

    template <typename T, typename... Props>
    using PreferResult = asio::prefer_result<T, Props...>;

    template <typename T, typename Prop>
    using QueryResult = asio::query_result<T, Prop>;

    template <typename T, typename... Props>
    using RequireResult = asio::require_result<T, Props...>;

    template <typename T, typename Prop>
    using RequireConceptResult = asio::require_concept_result<T, Prop>;

    namespace execution {
        template <typename... Properties>
        using AnyExecutor = asio::execution::any_executor<Properties...>;

        using BadExecutorException = asio::execution::bad_executor;
        using InvocableArchetype = asio::execution::invocable_archetype;

        template <typename T>
        using IsExecutor = asio::execution::is_executor<T>; 

        template <typename E>
        concept Executor = asio::execution::executor<E>;

        template <typename ProAlloc>
        using Allocator = asio::execution::allocator_t<ProAlloc>;

        using Blocking = asio::execution::blocking_t;

        using BlockingPossibly = asio::execution::blocking_t::possibly_t;

        constexpr Allocator ALLOCATOR = asio::execution::allocator;
        constexpr Blocking BLOCKING = asio::execution::blocking;
    }

    using AnyCompletionExecutor = asio::any_completion_executor;
    using AnyIOExecutor = asio::any_io_executor;
    using BadExecutorException = asio::bad_executor;
    using CancellationSignal = asio::cancellation_signal;
    using CancellationSlot = asio::cancellation_slot;
    using CancellationState = asio::cancellation_state;
    using CancellationType = asio::cancellation_type;
    using Config = asio::config;
    using ConfigService = asio::config_service;
    using ConfigFromConcurrencyHint = asio::config_from_concurrency_hint;
    using ConfigFromEnvironment = asio::config_from_env;
    using ConfigFromString = asio::config_from_string;
    using ConfigService = asio::config_service;
    using Coroutine = asio::coroutine;
    using Detached = asio::detached_t;
    using ErrorCode = asio::error_code;
    using ExecutionContext = asio::execution_context;
    using ExecutionContextId = asio::execution_context::id;
    using ExecutionContextService = asio::execution_context::service;
    using ExecutionContextServiceMaker = asio::execution_context::service_maker;
    using Executor = asio::executor;
    using ExecutorArgument = asio::executor_arg_t;
    using InvalidServiceOwnerException = asio::invalid_service_owner;
    using IOContext = asio::io_context;
    using IOContextExecutor = asio::io_context::executor_type;
    using IOContextService = asio::io_context::service;
    using IOContextStrand = asio::io_context::strand;
    using MultipleExceptions = asio::multiple_exceptions;
    using NoError = asio::no_error_t;
    using PartialAsTuple = asio::partial_as_tuple;
    using PartialRedirectError = asio::partial_redirect_error;
    using ServiceAlreadyExistsException = asio::service_already_exists;
    using StaticThreadPool = asio::static_thread_pool;
    using SystemContext = asio::system_context;
    using SystemError = asio::system_error;
    // using SystemExecutor = asio::system_executor;
    using Thread = asio::thread;
    using ThreadPool = asio::thread_pool;
    using ThreadPoolExecutor = asio::thread_pool::executor_type;
    // using YieldContext = asio::yield_context;

    namespace generic {
        using DatagramProtocol = asio::generic::datagram_protocol;
        using DatagramProtocolEndpoint = asio::generic::datagram_protocol::endpoint;
        using DatagramProtocolSocket = asio::generic::datagram_protocol::socket;
        using StreamProtocol = asio::generic::stream_protocol;
        using StreamProtocolEndpoint = asio::generic::stream_protocol::endpoint;
        using StreamProtocolSocket = asio::generic::stream_protocol::socket;
        using SequencePacketProtocol = asio::generic::seq_packet_protocol;
        using SequencePacketProtocolEndpoint = asio::generic::seq_packet_protocol::endpoint;
        using SequencePacketProtocolSocket = asio::generic::seq_packet_protocol::socket;
        using StreamProtocol = asio::generic::stream_protocol;
        using StreamProtocolEndpoint = asio::generic::stream_protocol::endpoint;
        using StreamProtocolIOStream = asio::generic::stream_protocol::iostream;
        using StreamProtocolSocket = asio::generic::stream_protocol::socket;
    }

    namespace ip {
        using Address = asio::ip::address;
        using AddressV4 = asio::ip::address_v4;
        using AddressV4Iterator = asio::ip::address_v4_iterator;
        using AddressV4Range = asio::ip::address_v4_range;
        using AddressV6 = asio::ip::address_v6;
        using AddressV6Iterator = asio::ip::address_v6_iterator;
        using AddressV6Range = asio::ip::address_v6_range;
        using BadAddressCastException = asio::ip::bad_address_cast;
        using ICMP = asio::ip::icmp;
        using ICMPEndpoint = asio::ip::icmp::endpoint;
        using ICMPResolver = asio::ip::icmp::resolver;
        using ICMPSocket = asio::ip::icmp::socket;
        using NetworkV4 = asio::ip::network_v4;
        using NetworkV6 = asio::ip::network_v6;
        using ResolverBase = asio::ip::resolver_base;
        using ResolverQueryBase = asio::ip::resolver_query_base;
        using TCP = asio::ip::tcp;
        using TCPAcceptor = asio::ip::tcp::acceptor;
        using TCPEndpoint = asio::ip::tcp::endpoint;
        using TCPIOStream = asio::ip::tcp::iostream;
        using TCPResolver = asio::ip::tcp::resolver;
        using TCPSocket = asio::ip::tcp::socket;
        using UDP = asio::ip::udp;
        using UDPEndpoint = asio::ip::udp::endpoint;
        using UDPResolver = asio::ip::udp::resolver;
        using UDPSocket = asio::ip::udp::socket;
        using V4Mapped = asio::ip::v4_mapped_t;

        using asio::ip::host_name;
        using asio::ip::make_address;
        using asio::ip::make_address_v4;
        using asio::ip::make_address_v6;
        using asio::ip::make_network_v4;
        using asio::ip::make_network_v6;

        template <typename InetProtocol>
        using BasicEndpoint = asio::ip::basic_endpoint<InetProtocol>;

        template <typename InetProtocol>
        using BasicResolver = asio::ip::basic_resolver<InetProtocol>;

        template <typename InetProtocol>
        using BasicResolverEntry = asio::ip::basic_resolver_entry<InetProtocol>;

        template <typename InetProtocol>
        using BasicResolverIterator = asio::ip::basic_resolver_iterator<InetProtocol>;

        template <typename InetProtocol>
        using BasicResolverResults = asio::ip::basic_resolver_results<InetProtocol>;

        template <typename InetProtocol>
        using BasicResolverQuery = asio::ip::basic_resolver_query<InetProtocol>;

        namespace multicast {
            using asio::ip::multicast::join_group;
            using asio::ip::multicast::leave_group;
            using asio::ip::multicast::outbound_interface;
            using asio::ip::multicast::hops;
            using asio::ip::multicast::enable_loopback;
        }
    }

    using SocketBase = asio::socket_base;

    using asio::async_connect;
    using asio::connect;

    namespace windows {
        #ifdef WIN32
        using ObjectHandle = asio::windows::object_handle;
        using OverlappedHandle = asio::windows::overlapped_handle;
        using OverlappedPointer = asio::windows::overlapped_ptr;
        using RandomAccessHandle = asio::windows::random_access_handle;
        using StreamHandle = asio::windows::stream_handle;

        template <typename Exec = AnyIOExecutor>
        using BasicObjectHandle = asio::windows::basic_object_handle<Exec>;

        template <typename Exec = AnyIOExecutor>
        using BasicOverlappedHandle = asio::windows::basic_overlapped_handle<Exec>;

        template <typename Exec = AnyIOExecutor>
        using BasicRandomAccessHandle = asio::windows::basic_random_access_handle<Exec>;
        #endif
    }
}
