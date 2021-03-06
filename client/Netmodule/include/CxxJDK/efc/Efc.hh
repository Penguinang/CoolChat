#ifndef __EFC_H__
#define __EFC_H__

#define EFC_VERSION "0.8.1"

#include "./EBase.hh"

//efc
#include "./inc/EA.hh"
#include "./inc/EAbstractCollection.hh"
#include "./inc/EAbstractList.hh"
#include "./inc/EAbstractMap.hh"
#include "./inc/EAbstractSet.hh"
#include "./inc/EAdler32.hh"
#include "./inc/EAlreadyConnectedException.hh"
#include "./inc/EArithmeticException.hh"
#include "./inc/EArray.hh"
#include "./inc/EArrayDeque.hh"
#include "./inc/EArrayIndexOutOfBoundsException.hh"
#include "./inc/EArrays.hh"
#include "./inc/EArrayList.hh"
#include "./inc/EAuthenticationException.hh"
#include "./inc/EBase64.hh"
#include "./inc/EBigDecimal.hh"
#include "./inc/EBigInteger.hh"
#include "./inc/EBits.hh"
#include "./inc/EBitSet.hh"
#include "./inc/EBson.hh"
#include "./inc/EBsonParser.hh"
#include "./inc/EBoolean.hh"
#include "./inc/EBufferedInputStream.hh"
#include "./inc/EBufferedOutputStream.hh"
#include "./inc/EByte.hh"
#include "./inc/EByteArrayInputStream.hh"
#include "./inc/EByteArrayOutputStream.hh"
#include "./inc/EByteBuffer.hh"
#include "./inc/ECalendar.hh"
#include "./inc/ECharacter.hh"
#include "./inc/ECheckedInputStream.hh"
#include "./inc/ECheckedOutputStream.hh"
#include "./inc/ECloseable.hh"
#include "./inc/EConcurrentModificationException.hh"
#include "./inc/EConnectException.hh"
#include "./inc/ECollection.hh"
#include "./inc/ECollections.hh"
#include "./inc/EComparable.hh"
#include "./inc/EComparator.hh"
#include "./inc/ECondition.hh"
#include "./inc/EConfig.hh"
#include "./inc/ECRC32.hh"
#include "./inc/EDataFormatException.hh"
#include "./inc/EDatagramPacket.hh"
#include "./inc/EDatagramSocket.hh"
#include "./inc/EDataInput.hh"
#include "./inc/EDataInputStream.hh"
#include "./inc/EDataOutput.hh"
#include "./inc/EDataOutputStream.hh"
#include "./inc/EDate.hh"
#include "./inc/EDeflater.hh"
#include "./inc/EDeflaterOutputStream.hh"
#include "./inc/EDeque.hh"
#include "./inc/EDictionary.hh"
#include "./inc/EDouble.hh"
#include "./inc/EFlushable.hh"
#include "./inc/EEmptyStackException.hh"
#include "./inc/EEnumeration.hh"
#include "./inc/EEOFException.hh"
#include "./inc/EEventListener.hh"
#include "./inc/EEventListenerProxy.hh"
#include "./inc/EEventObject.hh"
#include "./inc/EException.hh"
#include "./inc/EFile.hh"
#include "./inc/EFileInputStream.hh"
#include "./inc/EFileOutputStream.hh"
#include "./inc/EFilterOutputStream.hh"
#include "./inc/EFloat.hh"
#include "./inc/EFileFilter.hh"
#include "./inc/EFilenameFilter.hh"
#include "./inc/EFileNotFoundException.hh"
#include "./inc/EFork.hh"
#include "./inc/EHashMap.hh"
#include "./inc/EHashSet.hh"
#include "./inc/EIllegalArgumentException.hh"
#include "./inc/EIllegalStateException.hh"
#include "./inc/EIllegalThreadStateException.hh"
#include "./inc/EIndexOutOfBoundsException.hh"
#include "./inc/EInterfaceAddress.hh"
#include "./inc/EInterruptedIOException.hh"
#include "./inc/EInterruptible.hh"
#include "./inc/EGZIPInputStream.hh"
#include "./inc/EGZIPOutputStream.hh"
#include "./inc/EIdentityHashMap.hh"
#include "./inc/EIllegalBlockingModeException.hh"
#include "./inc/EInetAddress.hh"
#include "./inc/EInflater.hh"
#include "./inc/EInteger.hh"
#include "./inc/EInetSocketAddress.hh"
#include "./inc/EInflaterInputStream.hh"
#include "./inc/EIOException.hh"
#include "./inc/EIOStatus.hh"
#include "./inc/EIPAddressUtil.hh"
#include "./inc/EIterable.hh"
#include "./inc/EIterator.hh"
#include "./inc/ELinkedList.hh"
#include "./inc/EList.hh"
#include "./inc/ELLong.hh"
#include "./inc/ELock.hh"
#include "./inc/EMalformedURLException.hh"
#include "./inc/EMap.hh"
#include "./inc/EMatcher.hh"
#include "./inc/EMatchResult.hh"
#include "./inc/EMath.hh"
#include "./inc/ENavigableMap.hh"
#include "./inc/ENavigableSet.hh"
#include "./inc/ENetWrapper.hh"
#include "./inc/ENetworkInterface.hh"
#include "./inc/ENoConnectionPendingException.hh"
#include "./inc/ENoSuchElementException.hh"
#include "./inc/ENotYetBoundException.hh"
#include "./inc/ENotYetConnectedException.hh"
#include "./inc/ENumber.hh"
#include "./inc/EMulticastSocket.hh"
#include "./inc/ENumberFormatException.hh"
#include "./inc/EObject.hh"
#include "./inc/EObservable.hh"
#include "./inc/EObserver.hh"
#include "./inc/EOS.hh"
#include "./inc/EOutOfMemoryError.hh"
#include "./inc/EPattern.hh"
#include "./inc/EPipedInputStream.hh"
#include "./inc/EPipedOutputStream.hh"
#include "./inc/EPortUnreachableException.hh"
#include "./inc/EPrintStream.hh"
#include "./inc/EPriorityQueue.hh"
#include "./inc/EProcess.hh"
#include "./inc/EProperties.hh"
#include "./inc/EPushbackInputStream.hh"
#include "./inc/EQueue.hh"
#include "./inc/ERandom.hh"
#include "./inc/ERandomAccessFile.hh"
#include "./inc/EReference.hh"
#include "./inc/ERunnable.hh"
#include "./inc/ERuntimeException.hh"
#include "./inc/ESaslException.hh"
#include "./inc/ESecureRandom.hh"
#include "./inc/ESentry.hh"
#include "./inc/ESet.hh"
#include "./inc/EShort.hh"
#include "./inc/ESimpleCondition.hh"
#include "./inc/ESimpleEnumeration.hh"
#include "./inc/ESimpleLock.hh"
#include "./inc/ESimpleMap.hh"
#include "./inc/ESimpleStack.hh"
#include "./inc/ESimpleVector.hh"
#include "./inc/ESequenceInputStream.hh"
#include "./inc/EServerSocket.hh"
#include "./inc/ESharedPtr.hh"
#include "./inc/ESocket.hh"
#include "./inc/ESocketException.hh"
#include "./inc/ESortedMap.hh"
#include "./inc/ESortedSet.hh"
#include "./inc/ESpinLock.hh"
#include "./inc/ESSLServerSocket.hh"
#include "./inc/ESSLSocket.hh"
#include "./inc/EStack.hh"
#include "./inc/EStream.hh"
#include "./inc/EString.hh"
#include "./inc/EStringTokenizer.hh"
#include "./inc/ESynchronizeable.hh"
#include "./inc/ESystem.hh"
#include "./inc/EThread.hh"
#include "./inc/EThreadLocal.hh"
#include "./inc/EThreadLocalStorage.hh"
#include "./inc/EThreadUnCInitException.hh"
#include "./inc/EThrowable.hh"
#include "./inc/ETimer.hh"
#include "./inc/ETimerTask.hh"
#include "./inc/ETimeUnit.hh"
#include "./inc/EToDoException.hh"
#include "./inc/ETraits.hh"
#include "./inc/ETreeMap.hh"
#include "./inc/ETreeSet.hh"
#include "./inc/EUnknownHostException.hh"
#include "./inc/EUnknownServiceException.hh"
#include "./inc/EUnresolvedAddressException.hh"
#include "./inc/EUnsupportedAddressTypeException.hh"
#include "./inc/EUnsupportedEncodingException.hh"
#include "./inc/EUnsupportedOperationException.hh"
#include "./inc/EURI.hh"
#include "./inc/EURISyntaxException.hh"
#include "./inc/EURLDecoder.hh"
#include "./inc/EURLEncoder.hh"
#include "./inc/EURLString.hh"
#include "./inc/EVector.hh"
#include "./inc/concurrent/EAbstractExecutorService.hh"
#include "./inc/concurrent/EAbstractOwnableSynchronizer.hh"
#include "./inc/concurrent/EAbstractQueuedSynchronizer.hh"
#include "./inc/concurrent/EArrayBlockingQueue.hh"
#include "./inc/concurrent/EAtomic.hh"
#include "./inc/concurrent/EAtomicBoolean.hh"
#include "./inc/concurrent/EAtomicCounter.hh"
#include "./inc/concurrent/EAtomicDouble.hh"
#include "./inc/concurrent/EAtomicInteger.hh"
#include "./inc/concurrent/EAtomicLLong.hh"
#include "./inc/concurrent/EAtomicReference.hh"
#include "./inc/concurrent/ECallable.hh"
#include "./inc/concurrent/ECancellationException.hh"
#include "./inc/concurrent/EConcurrentHashMap.hh"
#include "./inc/concurrent/EConcurrentIntrusiveDeque.hh"
#include "./inc/concurrent/EConcurrentLinkedQueue.hh"
#include "./inc/concurrent/EConcurrentLiteQueue.hh"
#include "./inc/concurrent/EConcurrentSkipListMap.hh"
#include "./inc/concurrent/ECompletionService.hh"
#include "./inc/concurrent/ECopyOnWriteArrayList.hh"
#include "./inc/concurrent/ECountDownLatch.hh"
#include "./inc/concurrent/ECyclicBarrier.hh"
#include "./inc/concurrent/EExchanger.hh"
#include "./inc/concurrent/EExecutionException.hh"
#include "./inc/concurrent/EExecutor.hh"
#include "./inc/concurrent/EExecutorCompletionService.hh"
#include "./inc/concurrent/EExecutors.hh"
#include "./inc/concurrent/EExecutorService.hh"
#include "./inc/concurrent/EFuture.hh"
#include "./inc/concurrent/ELinkedBlockingQueue.hh"
#include "./inc/concurrent/ELinkedTransferQueue.hh"
#include "./inc/concurrent/ELockSupport.hh"
#include "./inc/concurrent/EMutexLinkedQueue.hh"
#include "./inc/concurrent/EOrderAccess.hh"
#include "./inc/concurrent/EReadWriteLock.hh"
#include "./inc/concurrent/EReentrantLock.hh"
#include "./inc/concurrent/EReentrantReadWriteLock.hh"
#include "./inc/concurrent/ERunnableFuture.hh"
#include "./inc/concurrent/ESemaphore.hh"
#include "./inc/concurrent/ESynchronousQueue.hh"
#include "./inc/concurrent/EThreadLocalRandom.hh"
#include "./inc/concurrent/EThreadPoolExecutor.hh"
#include "./inc/concurrent/ETimeoutException.hh"
#include "./inc/concurrent/EUnsafe.hh"

//efc::nio
#include "./nio/inc/EAsynchronousCloseException.hh"
#include "./nio/inc/EBufferOverflowException.hh"
#include "./nio/inc/EBufferUnderflowException.hh"
#include "./nio/inc/EByteChannel.hh"
#include "./nio/inc/ECancelledKeyException.hh"
#include "./nio/inc/EChannel.hh"
#include "./nio/inc/EChannelInputStream.hh"
#include "./nio/inc/EClosedChannelException.hh"
#include "./nio/inc/EClosedSelectorException.hh"
#include "./nio/inc/EConnectionPendingException.hh"
#include "./nio/inc/EDatagramChannel.hh"
#include "./nio/inc/EFileChannel.hh"
#include "./nio/inc/EFileDispatcher.hh"
#include "./nio/inc/EFileKey.hh"
#include "./nio/inc/EFileLock.hh"
#include "./nio/inc/EInvalidMarkException.hh"
#include "./nio/inc/EIOByteBuffer.hh"
#include "./nio/inc/EMappedByteBuffer.hh"
#include "./nio/inc/EMembershipKey.hh"
#include "./nio/inc/EMulticastChannel.hh"
#include "./nio/inc/ENativeThreadSet.hh"
#include "./nio/inc/ENonReadableChannelException.hh"
#include "./nio/inc/ENonWritableChannelException.hh"
#include "./nio/inc/EOverlappingFileLockException.hh"
#include "./nio/inc/EReadOnlyBufferException.hh"
#include "./nio/inc/ESelectableChannel.hh"
#include "./nio/inc/ESelectionKey.hh"
#include "./nio/inc/ESelector.hh"
#include "./nio/inc/EServerSocketChannel.hh"
#include "./nio/inc/ESocketChannel.hh"

//efc::cpp11
#include "./inc/cpp11/EScopeGuard.hh"

using namespace efc;
using namespace efc::nio;

#endif // !__EFC_H
