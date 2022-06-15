import numpy as np 

class LinearClassifier: 

    def classify(self, feature_matrix, theta, theta_0):
        """
        A classification function that uses theta and theta_0 to classify a set of
        data points.

        Args:
            feature_matrix - A numpy matrix describing the given data. Each row
                represents a single data point.
                    theta - A numpy array describing the linear classifier.
            theta - A numpy array describing the linear classifier.
            theta_0 - A real valued number representing the offset parameter.

        Returns: A numpy array of 1s and -1s where the kth element of the array is
        the predicted classification of the kth row of the feature matrix using the
        given theta and theta_0. If a prediction is GREATER THAN zero, it should
        be considered a positive classification.
        """
        (nsamples, nfeatures) = feature_matrix.shape
        predictions = np.zeros(nsamples)
        for i in range(nsamples):
            feature_vector = feature_matrix[i]
            prediction = np.dot(theta, feature_vector) + theta_0
            if (prediction > 0):
                predictions[i] = 1
            else:
                predictions[i] = -1
        return predictions
    
    def accuracy(self, preds, targets):
        """
        Given length-N vectors containing predicted and target labels,
        returns the percentage and number of correct predictions.
        """
        return (preds == targets).mean()

    def classifier_accuracy(self,
        classifier,
        train_feature_matrix,
        val_feature_matrix,
        train_labels,
        val_labels,
        **kwargs):
        """
        Trains a linear classifier and computes accuracy.
        The classifier is trained on the train data. The classifier's
        accuracy on the train and validation data is then returned.

        Args:
            classifier - A classifier function that takes arguments
                (feature matrix, labels, **kwargs) and returns (theta, theta_0)
            train_feature_matrix - A numpy matrix describing the training
                data. Each row represents a single data point.
            val_feature_matrix - A numpy matrix describing the validation
                data. Each row represents a single data point.
            train_labels - A numpy array where the kth element of the array
                is the correct classification of the kth row of the training
                feature matrix.
            val_labels - A numpy array where the kth element of the array
                is the correct classification of the kth row of the validation
                feature matrix.
            **kwargs - Additional named arguments to pass to the classifier
                (e.g. T or L)

        Returns: A tuple in which the first element is the (scalar) accuracy of the
        trained classifier on the training data and the second element is the
        accuracy of the trained classifier on the validation data.
        """
        theta, theta_0 = classifier(train_feature_matrix, train_labels, **kwargs)
        train_predictions = self.classify(train_feature_matrix, theta, theta_0)
        val_predictions = self.classify(val_feature_matrix, theta, theta_0)
        train_accuracy = self.accuracy(train_predictions, train_labels)
        validation_accuracy = self.accuracy(val_predictions, val_labels)
        return (train_accuracy, validation_accuracy)


class Perceptron(LinearClassifier):

    def perceptron_single_step_update(self, feature_vector, label, current_theta,
        current_theta_0):
        """
        Properly updates the classification parameter, theta and theta_0, on a
        single step of the perceptron algorithm.

        Args:
            feature_vector - A numpy array describing a single data point.
            label - The correct classification of the feature vector.
            current_theta - The current theta being used by the perceptron
                algorithm before this update.
            current_theta_0 - The current theta_0 being used by the perceptron
                algorithm before this update.

        Returns: A tuple where the first element is a numpy array with the value of
        theta after the current update has completed and the second element is a
        real valued number with the value of theta_0 after the current updated has
        completed.
        """
        if label * (np.dot(current_theta, feature_vector) + current_theta_0) <= 1e-7:
            return (current_theta + label * feature_vector, current_theta_0 + label)
        return (current_theta, current_theta_0)

    def perceptron(self, feature_matrix, labels, T):
        """
        Runs the full perceptron algorithm on a given set of data. Runs T
        iterations through the data set, there is no need to worry about
        stopping early.

        NOTE: Please use the previously implemented functions when applicable.
        Do not copy paste code from previous parts.

        NOTE: Iterate the data matrix by the orders returned by get_order(feature_matrix.shape[0])

        Args:
            feature_matrix -  A numpy matrix describing the given data. Each row
                represents a single data point.
            labels - A numpy array where the kth element of the array is the
                correct classification of the kth row of the feature matrix.
            T - An integer indicating how many times the perceptron algorithm
                should iterate through the feature matrix.

        Returns: A tuple where the first element is a numpy array with the value of
        theta, the linear classification parameter, after T iterations through the
        feature matrix and the second element is a real number with the value of
        theta_0, the offset classification parameter, after T iterations through
        the feature matrix.
        """
        (nsamples, nfeatures) = feature_matrix.shape
        theta = np.zeros(nfeatures)
        theta_0 = 0.0
        for t in range(T):
            for i in np.random.shuffle(nsamples): #get_order(nsamples)
                theta, theta_0 = self.perceptron_single_step_update(
                    feature_matrix[i], labels[i], theta, theta_0)
        return (theta, theta_0)

    def average_perceptron(self, feature_matrix, labels, T):
        """
        Runs the average perceptron algorithm on a given set of data. Runs T
        iterations through the data set, there is no need to worry about
        stopping early.

        NOTE: Please use the previously implemented functions when applicable.
        Do not copy paste code from previous parts.

        Args:
            feature_matrix -  A numpy matrix describing the given data. Each row
                represents a single data point.
            labels - A numpy array where the kth element of the array is the
                correct classification of the kth row of the feature matrix.
            T - An integer indicating how many times the perceptron algorithm
                should iterate through the feature matrix.

        Returns: A tuple where the first element is a numpy array with the value of
        the average theta, the linear classification parameter, found after T
        iterations through the feature matrix and the second element is a real
        number with the value of the average theta_0, the offset classification
        parameter, found after T iterations through the feature matrix.

        Hint: It is difficult to keep a running average; however, it is simple to
        find a sum and divide.
        """
        (nsamples, nfeatures) = feature_matrix.shape
        theta = np.zeros(nfeatures)
        theta_sum = np.zeros(nfeatures)
        theta_0 = 0.0
        theta_0_sum = 0.0
        for t in range(T):
            for i in np.random.shuffle(nsamples):  # get_order
                theta, theta_0 = self.perceptron_single_step_update(
                    feature_matrix[i], labels[i], theta, theta_0)
                theta_sum += theta
                theta_0_sum += theta_0
        return (theta_sum / (nsamples * T), theta_0_sum / (nsamples * T))


class Pegasos(LinearClassifier): 

    """ Pegasos: Primal Estimated sub-GrAdient solver for SVM"""

    def pegasos_single_step_update(self,
        feature_vector,
        label,
        L,
        eta,
        current_theta,
        current_theta_0):
        """
        Properly updates the classification parameter, theta and theta_0, on a
        single step of the Pegasos algorithm

        Args:
            feature_vector - A numpy array describing a single data point.
            label - The correct classification of the feature vector.
            L - The lamba value being used to update the parameters.
            eta - Learning rate to update parameters.
            current_theta - The current theta being used by the Pegasos
                algorithm before this update.
            current_theta_0 - The current theta_0 being used by the
                Pegasos algorithm before this update.

        Returns: A tuple where the first element is a numpy array with the value of
        theta after the current update has completed and the second element is a
        real valued number with the value of theta_0 after the current updated has
        completed.
        """
        mult = 1 - (eta * L)
        if label * (np.dot(feature_vector, current_theta) + current_theta_0) <= 1:
            return ((mult * current_theta) + (eta * label * feature_vector),
                    (current_theta_0) + (eta * label))
        return (mult * current_theta, current_theta_0)

    def pegasos(self, feature_matrix, labels, T, L):
        """
        Runs the Pegasos algorithm on a given set of data. Runs T
        iterations through the data set, there is no need to worry about
        stopping early.

        For each update, set learning rate = 1/sqrt(t),
        where t is a counter for the number of updates performed so far (between 1
        and nT inclusive).

        NOTE: Please use the previously implemented functions when applicable.
        Do not copy paste code from previous parts.

        Args:
            feature_matrix - A numpy matrix describing the given data. Each row
                represents a single data point.
            labels - A numpy array where the kth element of the array is the
                correct classification of the kth row of the feature matrix.
            T - An integer indicating how many times the algorithm
                should iterate through the feature matrix.
            L - The lamba value being used to update the Pegasos
                algorithm parameters.

        Returns: A tuple where the first element is a numpy array with the value of
        the theta, the linear classification parameter, found after T
        iterations through the feature matrix and the second element is a real
        number with the value of the theta_0, the offset classification
        parameter, found after T iterations through the feature matrix.
        """
        (nsamples, nfeatures) = feature_matrix.shape
        theta = np.zeros(nfeatures)
        theta_0 = 0
        count = 0
        for t in range(T):
            for i in get_order(nsamples):
                count += 1
                eta = 1.0 / np.sqrt(count)
                (theta, theta_0) = self.pegasos_single_step_update(
                    feature_matrix[i], labels[i], L, eta, theta, theta_0)
        return (theta, theta_0)