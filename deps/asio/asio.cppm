/**
 * @file asio.cppm
 * @module asio
 * @brief File containing the module declaration for asio
 * This module re-aliases all asio types to PascalCase.
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
        using BlockingPossibly = asio::execution::detail::blocking_t<>::possibly_t;
        using BlockingNever = asio::execution::detail::blocking_t<>::never_t;
        using BlockingAlways = asio::execution::detail::blocking_t<>::always_t;
        using BlockingAdaptation = asio::execution::blocking_adaptation_t;
        using BlockingAdaptationDisallowed = asio::execution::detail::blocking_adaptation_t<>::disallowed_t;
        using BlockingAdaptationAllowed = asio::execution::detail::blocking_adaptation_t<>::allowed_t;
        using Context = asio::execution::context_t;
        template <typename U>
        using ContextAs = asio::execution::context_as_t<U>;
        using Mapping = asio::execution::mapping_t;
        using MappingThread = asio::execution::detail::mapping_t<>::thread_t;
        using MappingNewThread = asio::execution::detail::mapping_t<>::new_thread_t;
        using MappingOther = asio::execution::detail::mapping_t<>::other_t;
        using Occupancy = asio::execution::occupancy_t;
        using OutstandingWork = asio::execution::outstanding_work_t;
        using OutstandingWorkUntracked = asio::execution::detail::outstanding_work_t<>::untracked_t;
        using OutstandingWorkTracked = asio::execution::detail::outstanding_work_t<>::tracked_t;
        template <typename InnerProperty>
        using PreferOnly = asio::execution::prefer_only<InnerProperty>;
        using Relationship = asio::execution::relationship_t;
        using RelationshipFork = asio::execution::detail::relationship_t<>::fork_t;
        using RelationshipContinuation = asio::execution::detail::relationship_t<>::continuation_t;

        constexpr Allocator ALLOCATOR = asio::execution::allocator;
        constexpr Blocking BLOCKING = asio::execution::blocking;
        constexpr BlockingAdaptation BLOCKING_ADAPTATION = asio::execution::blocking_adaptation;
        const BlockingAdaptationDisallowed DISALLOWED = asio::execution::detail::blocking_adaptation_t<>::disallowed;
        const BlockingAdaptationAllowed ALLOWED = asio::execution::detail::blocking_adaptation_t<>::allowed;
        constexpr Context CONTEXT = asio::execution::context;
        template <typename U>
        constexpr ContextAs CONTEXT_AS = asio::execution::context_as<U>;
        constexpr Mapping MAPPING = asio::execution::mapping;
        const MappingThread MAPPING_THREAD = asio::execution::detail::mapping_t<>::thread;
        const MappingNewThread MAPPING_NEW_THREAD = asio::execution::detail::mapping_t<>::new_thread;
        const MappingOther MAPPING_OTHER = asio::execution::detail::mapping_t<>::other;
        constexpr Occupancy OCCUPANCY = asio::execution::occupancy;
        constexpr OutstandingWork OUTSTANDING_WORK = asio::execution::outstanding_work;
        const OutstandingWorkUntracked OUTSTANDING_WORK_UNTRACKED = asio::execution::detail::outstanding_work_t<>::untracked;
        const OutstandingWorkTracked OUTSTANDING_WORK_TRACKED = asio::execution::detail::outstanding_work_t<>::tracked;
        template <typename InnerProperty>
        constexpr PreferOnly<InnerProperty> PREFER_ONLY = asio::execution::prefer_only<InnerProperty>{};
        constexpr Relationship RELATIONSHIP = asio::execution::relationship;
        const RelationshipFork RELATIONSHIP_FORK = asio::execution::detail::relationship_t<>::fork;
        const RelationshipContinuation RELATIONSHIP_CONTINUATION = asio::execution::detail::relationship_t<>::continuation;
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

    template <typename... Sigs>
    using AnyCompletionHandler = asio::any_completion_handler<Sigs...>;
    template <typename T, typename... Sigs>
    using AnyCompletionHandlerAllocator = asio::any_completion_handler_allocator<T, Sigs...>;


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
        using IPv4Address = asio::ip::address_v4;
        using IPv4AddressIterator = asio::ip::address_v4_iterator;
        using IPv4AddressRange = asio::ip::address_v4_range;
        using IPv6Address = asio::ip::address_v6;
        using IPv6AddressIterator = asio::ip::address_v6_iterator;
        using IPv6AddressRange = asio::ip::address_v6_range;
        using BadAddressCastException = asio::ip::bad_address_cast;
        using ICMP = asio::ip::icmp;
        using ICMPEndpoint = asio::ip::icmp::endpoint;
        using ICMPResolver = asio::ip::icmp::resolver;
        using ICMPSocket = asio::ip::icmp::socket;
        using IPv4NetworkAddress = asio::ip::network_v4;
        using IPv6NetworkAddress = asio::ip::network_v6;
        using ResolverBase = asio::ip::resolver_base;
        using ResolverQueryBase = asio::ip::resolver_query_base;
        using Tcp = asio::ip::tcp;
        using TcpAcceptor = asio::ip::tcp::acceptor;
        using TcpEndpoint = asio::ip::tcp::endpoint;
        using TcpIOStream = asio::ip::tcp::iostream;
        using TcpResolver = asio::ip::tcp::resolver;
        using TcpSocket = asio::ip::tcp::socket;
        using Udp = asio::ip::udp;
        using UdpEndpoint = asio::ip::udp::endpoint;
        using UdpResolver = asio::ip::udp::resolver;
        using UdpSocket = asio::ip::udp::socket;
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

    namespace local {
        #ifdef _POSIX_VERSION
        using SequencePacketProtocol = asio::local::seq_packet_protocol;
        using SequencePacketProtocolAcceptor = asio::local::seq_packet_protocol::acceptor;
        using SequencePacketProtocolEndpoint = asio::local::seq_packet_protocol::endpoint;
        using SequencePacketProtocolSocket = asio::local::seq_packet_protocol::socket;
        using StreamProtocol = asio::local::stream_protocol;
        using StreamProtocolAcceptor = asio::local::stream_protocol::acceptor;
        using StreamProtocolEndpoint = asio::local::stream_protocol::endpoint;
        using StreamProtocolInputOutputStream = asio::local::stream_protocol::iostream;
        using StreamProtocolSocket = asio::local::stream_protocol::socket;
        using DatagramProtocol = asio::local::datagram_protocol;
        using DatagramProtocolEndpoint = asio::local::datagram_protocol::endpoint;
        using DatagramProtocolSocket = asio::local::datagram_protocol::socket;

        using local::connect_pair;
        #endif
    }

    namespace posix {
        #ifdef _POSIX_VERSION
        using Descriptor = asio::posix::descriptor;
        using DescriptorBase = asio::posix::descriptor_base;
        using StreamDescriptor = asio::posix::stream_descriptor;

        template <typename Exec = AnyIOExecutor>
        using BasicDescriptor = asio::posix::basic_descriptor<Exec>;

        template <typename Exec = AnyIOExecutor>
        using BasicStreamDescriptor = asio::posix::basic_stream_descriptor<Exec>;
        #endif
    }

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
